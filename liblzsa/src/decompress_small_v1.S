//  decompress_small.S - space-efficient decompressor implementation for 8088
//
//  Copyright (C) 2019 Emmanuel Marty
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.

   .arch i8086
   .code16
   .intel_syntax noprefix
   .global lzsa1_decompress

//  ---------------------------------------------------------------------------
//  Decompress raw LZSA1 block
//  inputs:
//  * ds:si: raw LZSA1 block
//  * es:di: output buffer
//  output:
//  * ax:    decompressed size
//  ---------------------------------------------------------------------------

lzsa1_decompress:
   push si
   push di
   push es
   push ds
   push bp
   mov bp, sp
   mov di, ax
   mov ax, [bp+16]
   mov ds, ax
   mov si, [bp+14]
   mov es, dx

   push di                 // remember decompression offset
   cld                     // make string operations (lods, movs, stos..) move forward

   xor cx,cx

.decode_token:
   mov ax,cx               // clear ah - cx is zero from above or from after rep movsb in .copy_match
   lodsb                   // read token byte: O|LLL|MMMM
   mov dx,ax               // keep token in dl
   
   and al,0x70              // isolate literals length in token (LLL)
   mov cl,4
   shr al,cl               // shift literals length into place

   cmp al,0x07              // LITERALS_RUN_LEN?
   jne .got_literals       // no, we have the full literals count from the token, go copy

   lodsb                   // grab extra length byte
   add al,0x07              // add LITERALS_RUN_LEN
   jnc .got_literals       // if no overflow, we have the full literals count, go copy
   jne .mid_literals

   lodsw                   // grab 16-bit extra length
   .byte 0x81               // mask inc ah/lodsb
                           // (*like jmp short .got_literals but faster)

.mid_literals:
   inc ah                  // add 256
   lodsb                   // grab single extra length byte

.got_literals:
   xchg cx,ax
   rep movsb               // copy cx literals from ds:si to es:di

   test dl,dl              // check match offset size in token (O bit)
   js .get_long_offset

   dec cx
   xchg cx,ax              // ah to 0xff - cx was zero from the rep movsb above
   lodsb
   .byte 0x3C               // mask lodsw
                           // (*like jmp short .get_match_length but faster)

.get_long_offset:
   lodsw                   // Get 2-byte match offset

.get_match_length:
   xchg dx,ax              // dx: match offset  ax: original token
   and al,0x0F              // isolate match length in token (MMMM)
   add al,3                // add MIN_MATCH_SIZE

   cmp al,0x12              // MATCH_RUN_LEN?
   jne .got_matchlen       // no, we have the full match length from the token, go copy

   lodsb                   // grab extra length byte
   add al,0x12              // add MIN_MATCH_SIZE + MATCH_RUN_LEN
   jnc .got_matchlen       // if no overflow, we have the entire length
   jne .mid_matchlen       

   lodsw                   // grab 16-bit length
   test ax,ax              // bail if we hit EOD
   je short .done_decompressing

   .byte 0x81               // mask inc ah/lodsb
                           // (*like jmp short .got_literals but faster)
.mid_matchlen:
   inc ah                  // add 256
   lodsb                   // grab single extra length byte

.got_matchlen:
   xchg cx,ax              // copy match length into cx
   push ds                 // save ds:si (current pointer to compressed data)
   xchg si,ax          
   push es
   pop ds
   mov si,di               // ds:si now points at back reference in output data
   add si,dx
   rep movsb               // copy match
   xchg si,ax              // restore ds:si
   pop ds
   jmp short .decode_token // go decode another token

.done_decompressing:
   pop ax                  // retrieve the original decompression offset
   xchg ax,di              // compute decompressed size
   sub ax,di
   pop bp
   pop ds
   pop es
   pop di
   pop si
   retf 0x4

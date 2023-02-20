OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
SECTIONS
{
	/* segelf segment start markers for target text section. */
	".text!" . (NOLOAD) :
	{
		"__stext!" = .;
		KEEP(*(".crt0!"))
		*(".text!*" ".text.*!")
		*(".fartext!*" ".fartext.*!")
		*(".farrodata!*" ".farrodata.*!")
		"__etext!" = .;
	}

	/* Target text section. */
	.text . :
	{
		__stext = .;
		KEEP(*(".crt0"))
		*(.text ".text.*[^&]")
		*(".fartext.*[^&]")
		*(".farrodata.*[^&]")
		__etext = .;
	}

	/* segelf segment end markers for target text section. */
	".text&" . (NOLOAD) :
	{
		"__stext&" = .;
		KEEP(*(".crt0&"))
		*(".text&*" ".text.*&")
		*(".fartext&*" ".fartext.*&")
		*(".farrodata&*" ".farrodata.*&")
		"__etext&" = .;
		. = ALIGN (16);
	}

	.erom . (NOLOAD) :
	{
		. = ALIGN (16);
		"__erom" = .;
		"__erom!" = .;
		"__erom&" = .;
		. = .;
	}

	/* segelf segment start markers for target data section. */
	".data!" 0x10000 (NOLOAD) : AT(ADDR(".erom") + SIZEOF(".erom"))
	{
		"__sdata!" = .;
		KEEP(*(".crt0_data!"))
		*(".rodata!*" ".rodata.*!")
		*(".data!*" ".data.*!")
		*(".bss!*" ".bss.*!")
		"__edata!" = .;
		"__ebss!" = .;
	}

	/* Target data section. */
	".data" 0x10000: AT(ADDR(".erom") + SIZEOF(".erom"))
	{
		__sdata = .;
		KEEP(*(".crt0_data"))
		*(.rodata ".rodata.*[^&]")
		*(.data ".data.*[^&]")
		. = ALIGN (4);
		__edata = .;
	}
	"__ldata!" = 0;
	__ldata = SIZEOF(.data);
	"__ldata_words!" = 0;
	__ldata_words = (__ldata + 1) / 2;

	/* Target BSS section, with same segment bases as data section. */
	.bss . (NOLOAD) :
	{
		*(.bss ".bss.*[^&]")
		. = ALIGN (4);
		__ebss = .;
	}
	_heap = .; /* TODO: Is this a WWitch symbol? */
	"__lbss!" = 0;
	__lbss = SIZEOF(.bss);
	"__lbss_words!" = 0;
	__lbss_words = (__lbss + 1) / 2;

	/* segelf segment end markers for target data section. */
	".data&" . (NOLOAD) :
	{
		"__sdata&" = .;
		KEEP(*(".crt0_data&"))
		*(".rodata&*" ".rodata.*&")
		*(".data&*" ".data.*&")
		*(".bss&*" ".bss.*&")
		"__edata&" = .;
		"__ebss& " = .;
	}
}

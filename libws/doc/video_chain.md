WonderSwan Video Pipeline {#video_pipeline}
=========================

## Layers

The graphics hardware in the WonderSwan draws up to four layers at once, in
order from lowest to highest priority (bottom to top):

* SCR1
* SPR (low priority),
* SCR2
* SPR (high priority).

SCR1 and SCR2 refer to the two screens (or background layers) of the
WonderSwan. SPR refers to sprites. The priority flag allows putting individual
sprites above or below SCR2.

## Palettes

The graphics hardware provides sixteen palettes. SCR1 and SCR2 can access all
sixteen, while SPR are limited to the lower eight (8 - 15).

### "Mono" Mode

In "Mono" mode, a palette index goes through two stages:

* the color (0 - 7) is picked from the correct palette and index,
* the color is used as an index in the [shade LUT](@ref video_set_gray_lut) to acquire the final shade (0 - 15).

### "Color" Mode

In "Color" mode, palette data is read from [the color palette](@ref MEM_COLOR_PALETTE).
The ports from "Mono" mode are ignored (TODO - verify).

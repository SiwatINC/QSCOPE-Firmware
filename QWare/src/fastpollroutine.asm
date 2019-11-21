;fastpollroutine.asm
; use assembly code to probe as frequently as possible
.include "./m32u4at.inc"
    reti;
    cpi r16,c13;
    rep
    ok: nop
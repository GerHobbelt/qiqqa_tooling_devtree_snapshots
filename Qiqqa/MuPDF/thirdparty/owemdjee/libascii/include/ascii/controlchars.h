
#pragma once

/*
 *	#defines for non-printing ASCII characters
 */

#define NUL	0x00		/* ^@     null character */
#define EOS	0x00		/*        end of string */
#define SOH	0x01		/* ^A     start of heading */
#define STX	0x02		/* ^B     start of text */
#define ETX	0x03		/* ^C     end of text */
#define EOT	0x04		/* ^D     end of transmission */
#define ENQ	0x05		/* ^E     enquiry */
#define ACK	0x06		/* ^F     acknowledge */
#define BEL	0x07		/* ^G  \a bell / alert */
#define BS	0x08		/* ^H  \b backspace */
#define HT	0x09		/* ^I  \t horizontal tab */
#define LF	0x0a		/* ^J  \n newline */
#define NL	'\n'
#define VT	0x0b		/* ^K  \v vertical tab */
#define FF	0x0c		/* ^L  \f form feed */
#define CR	0x0d		/* ^M  \r carriage return */
#define SO	0x0e		/* ^N     shift out / dim */
#define SI	0x0f		/* ^O     shift in / bright */
#define DLE	0x10		/* ^P     data link escape */
#define DC1	0x11		/* ^Q     device control 1 */
#define XON	DC1         /*        resume */
#define DC2	0x12		/* ^R     device control 2 */
#define DC3	0x13		/* ^S     device control 3 */
#define XOFF	DC3     /*        pause */
#define DC4	0x14		/* ^T     device control 4 */
#define NAK	0x15		/* ^U     negative acknowledge */
#define SYN	0x16		/* ^V     synchronous idle / queue flush */
#define ETB	0x17		/* ^W     end of transmitted block */
#define CAN	0x18		/* ^X     cancel */
#define EM	0x19		/* ^Y     end of medium / cursor home */
#define SUB	0x1a		/* ^Z     substitute */
#define ESC	0x1b		/* ^[     escape */
#define FS	0x1c		/* ^\     file separator */
#define GS	0x1d		/* ^]     group separator */
#define RS	0x1e		/* ^^     record separator */
#define US	0x1f		/* ^_     unit separator */
#define SP	0x20		/* space */
#define DEL	0x7f		/* DEL    delete */



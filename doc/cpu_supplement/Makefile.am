#
#  COPYRIGHT (c) 1988-2002.
#  On-Line Applications Research Corporation (OAR).
#  All rights reserved.
#
#  $Id: Makefile.am,v 1.5.2.3 2010/06/11 10:55:13 ralf Exp $
#

PROJECT = cpu_supplement

include $(top_srcdir)/project.am
include $(top_srcdir)/main.am

REPLACE2 = $(PERL) $(top_srcdir)/tools/word-replace2

GENERATED_FILES = general.texi arm.texi avr.texi bfin.texi i386.texi lm32.texi \
    m68k.texi mips.texi powerpc.texi sh.texi sparc.texi

COMMON_FILES += $(top_srcdir)/common/cpright.texi

FILES = preface.texi

info_TEXINFOS = cpu_supplement.texi
cpu_supplement_TEXINFOS = $(FILES) $(COMMON_FILES) $(GENERATED_FILES)

#
#  Chapters which get automatic processing
#

general.texi: general.t
	$(BMENU2) -p "Preface" \
	    -u "Top" \
	    -n "" < $< > $@

arm.texi: arm.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

avr.texi: avr.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

bfin.texi: bfin.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

i386.texi: i386.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

lm32.texi: lm32.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

m68k.texi: m68k.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

mips.texi: mips.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

powerpc.texi: powerpc.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

sh.texi: sh.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

sparc.texi: sparc.t
	$(BMENU2) -p "" \
	    -u "Top" \
	    -n "" < $< > $@

CLEANFILES += cpu_supplement.info
CLEANFILES += cpu_supplement.info-1
CLEANFILES += cpu_supplement.info-2


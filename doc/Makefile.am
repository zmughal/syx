MAINTAINERCLEANFILES	= Makefile.in
info_TEXINFOS		= manual/syx.texi

SUFFIXES		= .info .pdf
info_docs		= manual/syx.info
pdf_docs		= manual/syx.pdf
html_docs		= manual/syx.html

.texi.info:
	$(MAKEINFO) $<

.texi.pdf:
	texi2pdf $<

.texi.html:
	$(MAKEINFO) --html $<

reference:
	cd $(top_srcdir) && doxygen Doxyfile

.PHONY: info pdf html doc man reference
info: manual/syx.texi $(info_docs)
pdf: manual/syx.texi $(pdf_docs)
html: manual/syx.texi $(html_docs)
doc: info pdf html reference
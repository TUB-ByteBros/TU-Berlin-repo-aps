WORKDIR = .

.PHONY: all

all: hello-world.pdf

# Test LaTeX build

hello-world.pdf: hello-world.tex
	latexmk -pdf -pdflatex="lualatex -interaction=nonstopmode -synctex=1 %O %S" $(WORKDIR)/hello-world.tex
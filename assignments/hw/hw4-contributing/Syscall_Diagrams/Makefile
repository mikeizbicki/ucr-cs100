all: dup_out dup_in oneFork multFork ForkandDup Legend complex_pipe input_redirection output_redirection

folders: bin left_overs

bin:
	mkdir bin

left_overs:
	mkdir left_overs

oneFork: folders
	latex src/oneFork.tex
	dvips oneFork.dvi
	ps2pdf oneFork.ps
	mv oneFork.pdf bin
	mv oneFork.* left_overs

multFork: folders
	latex src/multFork.tex
	dvips multFork.dvi
	ps2pdf multFork.ps
	mv multFork.pdf bin
	mv multFork.* left_overs

dup_out: folders
	latex src/dup_out.tex
	dvips dup_out.dvi
	ps2pdf dup_out.ps
	mv dup_out.pdf bin
	mv dup_out.* left_overs

dup_in: folders
	latex src/dup_in.tex
	dvips dup_in.dvi
	ps2pdf dup_in.ps
	mv dup_in.pdf bin
	mv dup_in.* left_overs

ForkandDup: folders
	latex src/ForkandDup.tex
	dvips ForkandDup.dvi
	ps2pdf ForkandDup.ps
	mv ForkandDup.pdf bin
	mv ForkandDup.* left_overs

Legend: folders
	latex src/Legend.tex
	dvips Legend.dvi
	ps2pdf Legend.ps
	mv Legend.pdf bin
	mv Legend.* left_overs

complex_pipe: folders
	latex src/complex_pipe.tex
	dvips complex_pipe.dvi
	ps2pdf complex_pipe.ps
	mv complex_pipe.pdf bin
	mv complex_pipe.* left_overs

input_redirection: folders
	latex src/input_redirection.tex
	dvips input_redirection.dvi
	ps2pdf input_redirection.ps
	mv input_redirection.pdf bin
	mv input_redirection.* left_overs

output_redirection: folders
	latex src/output_redirection.tex
	dvips output_redirection.dvi
	ps2pdf output_redirection.ps
	mv output_redirection.pdf bin
	mv output_redirection.* left_overs



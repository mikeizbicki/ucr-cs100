all: dup_out dup_in one_fork mult_fork simple_pipe legend complex_pipe input_redirection output_redirection

folders: bin left_overs

bin:
	mkdir bin

left_overs:
	mkdir left_overs

one_fork: folders
	latex src/one_fork.tex
	dvips one_fork.dvi
	ps2pdf one_fork.ps
	mv one_fork.pdf bin
	mv one_fork.* left_overs

mult_fork: folders
	latex src/mult_fork.tex
	dvips mult_fork.dvi
	ps2pdf mult_fork.ps
	mv mult_fork.pdf bin
	mv mult_fork.* left_overs

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

simple_pipe: folders
	latex src/simple_pipe.tex
	dvips simple_pipe.dvi
	ps2pdf simple_pipe.ps
	mv simple_pipe.pdf bin
	mv simple_pipe.* left_overs

legend: folders
	latex src/legend.tex
	dvips legend.dvi
	ps2pdf legend.ps
	mv legend.pdf bin
	mv legend.* left_overs

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



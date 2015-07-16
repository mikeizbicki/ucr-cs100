"vimrc file from tutorial

"yank whole file
map z ggvG$y

"map CTRL i to type out #include in insert mode
imap <c-i> #include

"common maps
" Toggle spell check
nmap <F5> :set spell!<enter>
" Comment a line by adding `//`
nmap <F2> ^i//<esc>
" Uncomment a line
nmap <F3> ^2x
" Yank a whole line
nmap Z ^v$y
" Indent the current line
nmap t ^i<tab><esc> 

"remove trailing spaces
fun! RmTrailSpaces()
    %s/\s\+$//ge
    noh
endfun

autocmd BufWrite *.c call RmTrailSpaces()
autocmd BufWrite *.cpp call RmTrailSpaces()

"cindent
autocmd VimEnter *.cpp set cindent

"change background
if strftime("%H") < 12
    set background=light
else
    set background=dark
endif

"change colorscheme
fun! VimColorMe()
    if &filetype == 'cpp'
        colorscheme ron
    elseif &filetype == 'modula2'
        colorscheme slate
    else
        colorscheme default
    endif
endfun

autocmd VimEnter * call VimColorMe()

"email abbreviation
iabbrev @@ youremail@mail.com

"copyright abbreviation
iabbrev copyR Copyright 2015 Mark Asfour, all rights reserved 

"5 commonly misspelled word fixes
iabbrev definately definitely
iabbrev alot a lot
iabbrev wierd weird
iabbrev recieve receive  
iabbrev thier their

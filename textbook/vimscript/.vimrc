"vimrc file from tutorial

map z ggvG$y

"map CTRL i to type out #include in insert mode
imap <c-i> #include

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

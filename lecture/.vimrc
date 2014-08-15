set number
set tabstop=4
set shiftwidth=4
set expandtab

set guioptions=

set spell spelllang=en_us 

"filetype plugin indent on
set smartindent
" for command mode
nmap <S-Tab> <<
" for insert mode
imap <S-Tab> <Esc><<i

" use ghc functionality for haskell files
  au Bufenter *.hs compiler ghc

  " switch on syntax highlighting
  syntax on

  " enable filetype detection, plus loading of filetype plugins
  filetype plugin on

  " configure browser for haskell_doc.vim
  let g:haddock_browser = "/usr/bin/firefox"
"  let g:ghc = "/usr/bin/ghc"
"  let g:haddock_docdir = "/usr/share/doc/ghc-doc/html"
    "let g:haddock_browser = "C:/Program Files/Opera/Opera.exe"
    "let g:haddock_browser = "C:/Program Files/Mozilla Firefox/firefox.exe"
    "let g:haddock_browser = "C:/Program Files/Internet Explorer/IEXPLORE.exe"


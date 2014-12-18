"tabs and spaces
set shiftwidth=4	"1 tab == 4 spaces
set tabstop=4		"<TAB> == 4 spaces
set softtabstop=4	"<TAB> and backspace
set smarttab		"smart tab
set ai			"set auto indent
set si			"set smart indent
set copyindent		"use exisiting indents for new indents
set preserveindent	"save as much indent structure as possible

"Go to vim.wikia.com/wiki/Indenting_source_code for more information on tab and spaces

"UI Config
set number			"line number
set showmatch			"highlight matching [({})]
set mat=2			"for showmatch, set how many tenth of second it blinks
set ruler			"show current position
set magic			"magic for regular expression
set confirm			"ask to save file
set showcmd			"display incomplete command in the lower right corner of the console
set undolevels=1000 		"let vim allow 1000 undos
syntax enable			"enable syntax highlighting
"set list			"show invisible characters
"set autochdir			"automatically cd into the dir the file vim is editing
"set wildmenu			"autocomplete for command line
"set lazydraw			"disbale redraw and get a fester macro
"set history=700		"set the lines of history vim remembers to 700
"set so=5;			"keep at least 5 lines above/below
"set cmdheight=2		"set the height of the command bar to 2
"colorscheme default		"different colorscheme built in with vim
"colorscheme zellner 
"colorscheme torte 
"colorscheme slate 
"colorscheme shine 
"colorscheme ron 
"colorscheme peachpuff 
"colorscheme pablo 
"colorscheme murphy 
"colorscheme morning 
"colorscheme evening 
"colorscheme darkblue 
"colorscheme blue 
"colorscheme delek 
"colorscheme elflord 
"colorscheme koehler 
"colorscheme desert

"Searching
set incsearch			   "search as char are entered
set hlsearch			   "highlight matches
set smartcase			   "smart with case search
map <silent> <leader><cr> :noh<cr> "disable highlight with <cr>

"Go to vim.wilia.com/wiki/Searching for more explanation on search in vim

"Folding
set foldenable	      "enable folds
set foldlevelstart=10 "prevent too many folds
set foldmethod=indent "set fold based on indentation
		      "can also be marker, manual, expr, syntax, or diff
		      "check :help for more information

"Movement
set mouse=a				     "mouse support in console
set mousehide				 "hide cursor when typing
set cursorline				     "underline current line that the current line is on
hi CursorLine term=none cterm=none ctermbg=3 "highlight cursor
nnoremap j gj
nnoremap k gk 				     "j, k does not skip long lines
set scrolloff=5					 "minimum lines to keep above and below
"nnoremap BB ^
"nnoremap EE $				     "use BB and EE instead of ^ and $
"map <space> /				     "set <space> to / (search)
"map <c-space> ?			     "set <ctrl> + <space> to ? (backward search)
"nnoremap gV `[v`]			     "selects the block of characters in INSERT last time

"Go to nerd-hacking.blogspot.com/2006/05/vim-movements.html for tips on movement in vim

"For Typing and Spell-checking
setlocal spell spelllang=en_us "set spell-check to US English
set complete+=kspell



".vimrc Config for Solarized Colorscheme
"syntax enable
"set background=dark "for dark background
"set background=light "for light background
"colorscheme solarized

"if user wants to different background in GUI and temrminal
"if has('gui_running')
"	set background=light
"else
"	set background=dark
"endif

".vimrc Config for NERDcommenter
"filetype plugin on

".vimrc Config for EasyMotion
"let g:EasyMotion_do_mapping = 0 " Disable default mappings

" Bi-directional find motion
" Jump to anywhere you want with minimal keystrokes, with just one key binding.
" `s{char}{label}`
"nmap s <Plug>(easymotion-s)
" or
" `s{char}{char}{label}`
" Need one more keystroke, but on average, it may be more comfortable.
"nmap s <Plug>(easymotion-s2)

" Turn on case sensitive feature
"let g:EasyMotion_smartcase = 1

" JK motions: Line motions
"map <Leader>j <Plug>(easymotion-j)
"map <Leader>k <Plug>(easymotion-k)

".vimrc Config for Gundo
"nnoremap<F5> :GundoToggle<CR>
"adjust width, height, and preview buttom
"below are all same as default
"let g:gundo_width = 45
"let g:gundo_preview_height = 15
"let g:gundo_right = 0


call plug#begin()

Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
Plug 'mattn/emmet-vim'
Plug 'jiangmiao/auto-pairs'
Plug 'kien/ctrlp.vim'
Plug 'vim-airline/vim-airline'
Plug 'rust-lang/rust.vim'
"Colorschemes
Plug 'NLKNguyen/papercolor-theme'

call plug#end()

"Mappings
let g:mapleader = ','
map <C-n> :NERDTreeToggle<CR>
let NERDTreeShowHidden=1

"Shared clipboard
set clipboard+=unnamedplus

"Swithing between the windows
noremap <C-j> <C-w>j
noremap <C-k> <C-w>k
noremap <C-l> <C-w>l
noremap <C-h> <C-w>h

"Color Theme
colorscheme PaperColor

"Airline
let g:airline_powerline_fonts = 1 
let g:airline#extensions#keymap#enabled = 0 
let g:airline_section_z = "\ue0a1:%l/%L Col:%c"
let g:Powerline_symbols='unicode' 
let g:airline#extensions#xkblayout#enabled = 0 

"Clipboard
set clipboard+=unnamedplus

"Tabulations
set expandtab
set smarttab
set tabstop=4
set softtabstop=4
set shiftwidth=4

"Search
set hlsearch
set incsearch

"Indentations
filetype plugin indent on

"Numerations
set number

"Syntax
syntax on

"Sound Off
set noerrorbells
set novisualbell

"Mouse
set mouse=a

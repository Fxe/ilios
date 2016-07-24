set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'

Bundle 'scrooloose/nerdtree'
Bundle 'kien/ctrlp.vim'
Bundle 'rking/ag.vim'
Bundle 'nanotech/jellybeans.vim'
Bundle 'tpope/vim-fugitive'

call vundle#end()            " required
filetype plugin indent on    " required

nmap <leader>n :NERDTreeToggle<CR>
nmap <F5> !make<CR>
nmap <leader>t :CtrlP<CR>

nmap <C-M> :tabp<CR>
nmap <C-N> :tabn<CR>
nmap <C-T> :tabnew<CR>

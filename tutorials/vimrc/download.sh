#!/usr/bin/env bash 
#a script that downloads .vimrc and the bundles from atan009/vimrc

#move to $HOME to sort everything later
cd

#download the repo
git clone https://github.com/atan009/vimrc

#check if .vimrc and .vim already exist
#if yes, rename the file and move it to a folder called old_vim
#if no, create .vim folder, move autoload and bundle into that .vim folder

#go back to $HOME
cd

#if statement to check if .vim and .vimrc already exist
if test -e .vim 
then
	#if .vim exist, check if .vimrc exists
	if test -e .vimrc
	#if both exist, create a dir and move both
	then
		mkdir old_vim_config
		mv .vim old_vim_config
		mv .vimrc old_vim_config
	#if only .vim exists
	else
	 	 mkdir old_vim_config
	 	 mv .vim old_vim_config
	fi
else
	#if only .vimrc exists
	if test -e .vimrc
	then
		mkdir old_vim_config
		mv .vimrc
	fi
fi

#go to the temp folder and move .vimrc and .vim out to desktop
cd
cd vimrc 
mv .vim ..
mv .vimrc ..
cd
rm -rf vimrc

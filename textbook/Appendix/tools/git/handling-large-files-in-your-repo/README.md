# Adjusting Git Repository for Large Files

Storing large files in a repo has the potential to consume a lot of the systems resources so you may run into a few errors.

A common message that implies that you have run out of disk space on a server is the following error message:

  ```
    fatal: unable to create thread: Resource temporarily unavailable
    error: pack-objects died with strange error
  ```

If you have a repository with lots of large files, re-packing during commands such as "git push" may take up all available resources on a server, affecting the rest of the processes. 

Git uses packs to condense the size of files to make movement more efficient and shrink the size of a repo overall. 
By doing this, git has reduced the load on mirror systems, backup engines, disk storage, etc.

In order to get around these errors we need to adjust our configurations.
By typing in the following lines into your terminal, you will limit the amount of memory that packing may take.

  ```
  git config --global pack.windowMemory "100m"
  git config --global pack.SizeLimit "100m"
  git config --global pack.threads "1"
  ```

**NOTE**: 
The numbers that you configure can be adjusted as you wish.
As a rule of thumb:

  * "Larger window sizes may allow your system to process a smaller number of large pack files more quickly."
  
  * "Smaller window sizes will negatively affect performance due to increased calls to the operating system’s memory manager, but may improve performance when accessing a large number of large pack files."
  
  [more info](https://gforge.com/gf/project/gforge5/wiki/?pagename=Tweaking+GIT+repositories+for+large+binary+files)

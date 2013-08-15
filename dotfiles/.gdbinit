handle SIG32 nostop noprint
set print pretty on

#set print elements 10

set pagination off
set print null-stop on

def prs
  print /s $1.c_str()
end


set auto-load safe-path /

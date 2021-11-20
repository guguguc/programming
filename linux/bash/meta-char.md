## Command
### ;
command1; command2; ...
command2 will be executed, whether or not command1 succeed or failed
cat nothing; ls
### &&
command1 && command2 && ...
command2 will be executed only if command1 succeed
### ||
command1 || command2 || ...
command2 will be executed only if command1 failed
ls repo || mkdir repo

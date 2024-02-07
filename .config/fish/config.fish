if status is-interactive
    # Commands to run in interactive sessions can go here
    export XDG_RUNTIME_DIR="/run/user/1000"
end

if status is-login
    source ~/.local/bin/wrappedhl
end

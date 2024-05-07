vim.o.tabstop = 4
vim.o.expandtab = true
vim.o.softtabstop = 4
vim.o.shiftwidth = 4
vim.o.numberwidth = 4
vim.o.number = true
vim.o.relativenumber = true

vim.cmd(":command WQ wq")
vim.cmd(":command Wq wq")
vim.cmd(":command W w")
vim.cmd(":command Q q")

vim.g.mapleader = " "

vim.filetype.add({
    pattern = { [".*/hypr/.*.conf"] = "hyprlang" },
})

vim.cmd(":set spell spelllang=ru,en_us")

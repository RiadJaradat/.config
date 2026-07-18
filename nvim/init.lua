vim.g.have_nerd_font = true

------------------------------------------------------------
-- BASIC SETTINGS
------------------------------------------------------------

vim.o.number = true
vim.o.relativenumber = true
vim.o.showmode = false
vim.o.breakindent = true
vim.o.undofile = true
vim.o.ignorecase = true
vim.o.smartcase = true
vim.o.confirm = true
vim.o.autoindent = true
vim.o.smartindent = true
vim.o.expandtab = true
vim.o.shiftwidth = 4
vim.o.tabstop = 4
vim.o.softtabstop = 4

vim.opt.termguicolors = true

vim.schedule(function()
	vim.o.clipboard = "unnamedplus"
end)

------------------------------------------------------------
-- KEYMAPS
------------------------------------------------------------

-- formatter
vim.keymap.set("n", "<C-S-i>", function()
	require("conform").format({
		async = true,
		lsp_fallback = true,
	})
end)

vim.keymap.set("n", "<Esc>", "<cmd>nohlsearch<CR>")
vim.keymap.set("n", "<leader>q", "<cmd>qa<cr>") -- quit all

-- Window navigation
vim.keymap.set("n", "<C-h>", "<C-w><C-h>")
vim.keymap.set("n", "<C-l>", "<C-w><C-l>")
vim.keymap.set("n", "<C-j>", "<C-w><C-j>")
vim.keymap.set("n", "<C-k>", "<C-w><C-k>")

-- Neo-tree
vim.keymap.set("n", "<C-n>", ":Neotree toggle<CR>")

-- Tabs
vim.keymap.set("n", "<M-h>", ":tabprevious<CR>")
vim.keymap.set("n", "<M-l>", ":tabnext<CR>")

-- Disable arrow keys
local modes = { "n", "i", "v" }
local keys = { "<Up>", "<Down>", "<Left>", "<Right>" }

for _, mode in ipairs(modes) do
	for _, key in ipairs(keys) do
		vim.keymap.set(mode, key, "<Nop>", {
			noremap = true,
			silent = true,
		})
	end
end

------------------------------------------------------------
-- YANK HIGHLIGHT
------------------------------------------------------------

vim.api.nvim_create_autocmd("TextYankPost", {
	desc = "Highlight when yanking text",
	group = vim.api.nvim_create_augroup("highlight-yank", { clear = true }),

	callback = function()
		vim.highlight.on_yank()
	end,
})

------------------------------------------------------------
-- DIAGNOSTICS
------------------------------------------------------------

vim.diagnostic.config({
	update_in_insert = false,
	severity_sort = true,

	virtual_text = {
		prefix = "●",
		spacing = 4,
	},

	underline = true,

	float = {
		border = "rounded",
		source = "if_many",
	},
})

vim.keymap.set("n", "<leader>q", vim.diagnostic.setloclist)

------------------------------------------------------------
-- LAZY.NVIM BOOTSTRAP
------------------------------------------------------------

local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"

if not (vim.uv or vim.loop).fs_stat(lazypath) then
	vim.fn.system({
		"git",
		"clone",
		"--filter=blob:none",
		"https://github.com/folke/lazy.nvim.git",
		"--branch=stable",
		lazypath,
	})
end

vim.opt.rtp:prepend(lazypath)

------------------------------------------------------------
-- PLUGINS
------------------------------------------------------------

require("lazy").setup({

	----------------------------------------------------------
	-- terminal
	----------------------------------------------------------
	{
		"akinsho/toggleterm.nvim",
		version = "*",
		config = true,
	},
	----------------------------------------------------------
	-- README
	----------------------------------------------------------
	{
		"iamcco/markdown-preview.nvim",
		cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
		build = "cd app && npm install",
		init = function()
			vim.g.mkdp_filetypes = { "markdown" }
		end,
		ft = { "markdown" },
	},

	----------------------------------------------------------
	-- TREESITTER (Updated config syntax)
	----------------------------------------------------------
	{
		"nvim-treesitter/nvim-treesitter",
		build = ":TSUpdate",
		config = function()
			require("nvim-treesitter").setup({
				ensure_installed = {
					"lua",
					"cpp",
					"c",
					"python",
					"javascript",
				},
				highlight = {
					enable = true,
				},
			})
		end,
	},

	----------------------------------------------------------
	-- COMMENTER
	----------------------------------------------------------
	{
		"numToStr/Comment.nvim",
		config = function()
			require("Comment").setup()
		end,
	},

	----------------------------------------------------------
	-- MASON (Moved up so formatters/LSP can hook into it safely)
	----------------------------------------------------------
	{
		"williamboman/mason.nvim",
		config = function()
			require("mason").setup()
		end,
	},

	----------------------------------------------------------
	-- FORMATTING
	----------------------------------------------------------
	{
		"stevearc/conform.nvim",
		opts = {
			formatters_by_ft = {
				lua = { "stylua" },
				cpp = { "clang_format" },
				c = { "clang_format" },
				python = { "black" },
				javascript = { "prettier" },
			},
			format_on_save = {
				timeout_ms = 500,
				lsp_fallback = true,
			},
		},
	},

	{
		"zapling/mason-conform.nvim",
		dependencies = {
			"williamboman/mason.nvim",
			"stevearc/conform.nvim",
		},
		opts = {
			ensure_installed = {
				"stylua",
				"clang-format",
				"black",
				"prettier",
			},
		},
	},

	----------------------------------------------------------
	-- AUTOPAIR
	----------------------------------------------------------
	{
		"windwp/nvim-autopairs",
		event = "InsertEnter",
		config = function()
			require("nvim-autopairs").setup({})
		end,
	},

	----------------------------------------------------------
	-- THEME
	----------------------------------------------------------
	{
		"folke/tokyonight.nvim",
		lazy = false,
		priority = 1000,
		config = function()
			require("tokyonight").setup({
				transparent = true,
				styles = {
					sidebars = "transparent",
					floats = "transparent",
				},
			})

			vim.cmd.colorscheme("tokyonight")
		end,
	},
	----------------------------------------------------------
	-- ICONS
	----------------------------------------------------------
	{
		"nvim-tree/nvim-web-devicons",
	},

	----------------------------------------------------------
	-- LUALINE
	----------------------------------------------------------
	{
		"nvim-lualine/lualine.nvim",
		dependencies = {
			"nvim-tree/nvim-web-devicons",
		},
		config = function()
			require("lualine").setup({
				options = {
					theme = "tokyonight",
					icons_enabled = true,
				},
			})
		end,
	},

	----------------------------------------------------------
	-- TELESCOPE
	----------------------------------------------------------
	{
		"nvim-telescope/telescope.nvim",
		branch = "0.1.x",
		dependencies = {
			"nvim-lua/plenary.nvim",
		},
	},

	----------------------------------------------------------
	-- NEO TREE
	----------------------------------------------------------
	{
		"nvim-neo-tree/neo-tree.nvim",
		branch = "v3.x",
		dependencies = {
			"nvim-lua/plenary.nvim",
			"nvim-tree/nvim-web-devicons",
			"MunifTanjim/nui.nvim",
		},
		config = function()
			require("neo-tree").setup({
				filesystem = {
					window = {
						mappings = {
							["P"] = function(state)
								local node = state.tree:get_node()
								local path = node.path
								vim.fn.jobstart({ "feh", path }, { detach = true })
							end,
						},
					},
				},
			})
		end,
	},

	----------------------------------------------------------
	-- ERROR LENS
	----------------------------------------------------------
	{
		"chikko80/error-lens.nvim",
		event = "LspAttach",
		opts = {},
	},

	----------------------------------------------------------
	-- MASON LSPCONFIG
	----------------------------------------------------------
	{
		"williamboman/mason-lspconfig.nvim",
		dependencies = {
			"williamboman/mason.nvim",
		},
		config = function()
			require("mason-lspconfig").setup({
				ensure_installed = {
					"lua_ls",
					"clangd",
				},
			})
		end,
	},

	----------------------------------------------------------
	-- LSP
	----------------------------------------------------------
	{
		"neovim/nvim-lspconfig",
		dependencies = {
			"hrsh7th/cmp-nvim-lsp",
		},
		config = function()
			local capabilities = require("cmp_nvim_lsp").default_capabilities()

			vim.lsp.config("lua_ls", {
				capabilities = capabilities,
			})

			vim.lsp.config("clangd", {
				capabilities = capabilities,
			})

			vim.lsp.enable("lua_ls")
			vim.lsp.enable("clangd")
		end,
	},

	----------------------------------------------------------
	-- AUTOCOMPLETE
	----------------------------------------------------------
	{
		"hrsh7th/nvim-cmp",
		dependencies = {
			"hrsh7th/cmp-nvim-lsp",
			"hrsh7th/cmp-buffer",
			"hrsh7th/cmp-path", -- Cleaned up and kept right alongside autocomplete dependencies
			"L3MON4D3/LuaSnip",
			"saadparwaiz1/cmp_luasnip",
		},
		config = function()
			local cmp = require("cmp")

			cmp.setup({
				snippet = {
					expand = function(args)
						require("luasnip").lsp_expand(args.body)
					end,
				},
				mapping = cmp.mapping.preset.insert({
					["<C-b>"] = cmp.mapping.scroll_docs(-4),
					["<C-f>"] = cmp.mapping.scroll_docs(4),
					["<C-m>"] = cmp.mapping.complete(),
					["<C-e>"] = cmp.mapping.abort(),
					["<CR>"] = cmp.mapping.confirm({
						select = true,
					}),
					["<C-n>"] = cmp.mapping.select_next_item(),
					["<C-p>"] = cmp.mapping.select_prev_item(),
				}),
				sources = cmp.config.sources({
					{ name = "nvim_lsp" },
					{ name = "luasnip" },
					{ name = "path" },
				}, {
					{ name = "buffer" },
				}),
			})
		end,
	},

	----------------------------------------------------------
	-- FINE CMDLINE
	----------------------------------------------------------
	{
		"VonHeikemen/fine-cmdline.nvim",
		dependencies = {
			"MunifTanjim/nui.nvim",
		},
		config = function()
			require("fine-cmdline").setup({
				cmdline = {
					enable_keymaps = true,
					smart_history = true,
					prompt = ": ",
				},
				popup = {
					position = "50%",
					size = {
						width = "60%",
					},
					border = {
						style = "rounded",
					},
					win_options = {
						winhighlight = "Normal:Normal,FloatBorder:FloatBorder",
					},
				},
			})

			vim.keymap.set("n", ":", "<cmd>FineCmdline<CR>", { noremap = true })
			vim.keymap.set("v", ":", "<C-u>FineCmdline<CR>", { noremap = true })
		end,
	},

	----------------------------------------------------------
	-- NOTIFY
	----------------------------------------------------------
	{
		"rcarriga/nvim-notify",
		config = function()
			local notify = require("notify")
			notify.setup({
				background_colour = "#000000",
				timeout = 3000,
			})
			vim.notify = notify
		end,
	},
})

require("toggleterm").setup({
	open_mapping = [[<C-t>]],
})

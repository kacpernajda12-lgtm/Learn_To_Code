#!/bin/bash
# 01 - Git Basics
# Git is a version control system — it tracks every change you make to your files.
# Run this script in Git Bash or MSYS2.

set -e  # stop on first error

DEMO_DIR="$HOME/git_demo_01"
rm -rf "$DEMO_DIR"
mkdir "$DEMO_DIR" && cd "$DEMO_DIR"

echo "=== Working in: $DEMO_DIR ==="


# =========================================================
# INIT — turn a folder into a git repository
# =========================================================
git init
# Creates a hidden .git folder — this is the entire history of your project


# =========================================================
# CONFIG — who are you?
# (skip if already set globally)
# =========================================================
git config user.name  "Your Name"
git config user.email "you@example.com"
# Use --global to set it once for all repos:
#   git config --global user.name "Your Name"


# =========================================================
# CREATE FILES and check STATUS
# =========================================================
echo "# My Project" > README.md
echo "print('hello')" > main.py

git status
# Shows:
#   Untracked files: README.md, main.py  (git sees them but doesn't track yet)


# =========================================================
# ADD — stage files (tell git "include this in the next commit")
# =========================================================
git add README.md        # stage one file
git add main.py          # stage another
# git add .              # stage everything in the current folder
# git add -p             # interactive: choose which chunks to stage

git status
# Shows: Changes to be committed (green)


# =========================================================
# COMMIT — save a snapshot of staged files
# =========================================================
git commit -m "Initial commit: add README and main.py"
# -m "message"  — short description of WHAT changed and WHY
# Good:  "fix login crash when email is empty"
# Bad:   "fix stuff"


# =========================================================
# MAKE CHANGES and see the DIFF
# =========================================================
echo "print('world')" >> main.py

git diff            # shows unstaged changes (what changed since last add)
git add main.py
git diff --staged   # shows staged changes (what will go into the commit)

git commit -m "Add world print to main.py"


# =========================================================
# LOG — browse the commit history
# =========================================================
git log                         # full log
git log --oneline               # one line per commit
git log --oneline --graph       # with branch graph
git log --oneline -5            # last 5 commits
git log --author="Your Name"    # filter by author
git log --since="2 days ago"    # filter by date


# =========================================================
# SHOW — inspect a specific commit
# =========================================================
HASH=$(git log --oneline | tail -1 | cut -d' ' -f1)
git show "$HASH"        # shows the full diff of that commit


# =========================================================
# .GITIGNORE — files git should never track
# =========================================================
mkdir -p __pycache__
echo "cache" > __pycache__/data.pyc
echo "secret" > .env

cat > .gitignore << 'EOF'
# Python
__pycache__/
*.pyc
*.pyo

# Environment
.env
.venv/
venv/

# OS
.DS_Store
Thumbs.db

# Build output
/dist/
/build/
*.exe
EOF

git add .gitignore
git commit -m "Add .gitignore"

git status   # __pycache__ and .env are now ignored


# =========================================================
# CLEANUP
# =========================================================
cd ~
echo ""
echo "Done! Repo is at: $DEMO_DIR"
echo "Explore it with: cd $DEMO_DIR && git log --oneline"

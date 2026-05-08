#!/bin/bash
# 02 - Branches
# A branch is an independent line of development.
# main/master = stable production code
# feature branches = work in progress, safe from breaking main

set -e

DEMO_DIR="$HOME/git_demo_02"
rm -rf "$DEMO_DIR"
mkdir "$DEMO_DIR" && cd "$DEMO_DIR"

git init
git config user.name  "Demo User"
git config user.email "demo@example.com"

# Create initial commit on main
echo "# App v1.0" > README.md
echo "def greet(): return 'hello'" > app.py
git add .
git commit -m "Initial commit on main"


# =========================================================
# CREATE and SWITCH branches
# =========================================================
git branch                          # list branches (* = current)
git branch feature/login            # create branch (doesn't switch)
git switch feature/login            # switch to it
# shortcut: git switch -c feature/login  (create + switch in one step)

echo "def login(user): pass" >> app.py
git add app.py
git commit -m "Add login function skeleton"

echo "def logout(user): pass" >> app.py
git add app.py
git commit -m "Add logout function"

git log --oneline       # 3 commits on feature/login


# =========================================================
# SWITCH BACK to main — feature changes are not here
# =========================================================
git switch main
cat app.py              # only has greet() — login/logout not here yet
git log --oneline       # only 1 commit


# =========================================================
# MERGE — bring feature changes into main
# =========================================================
git merge feature/login --no-ff -m "Merge feature/login into main"
# --no-ff creates a merge commit even if a fast-forward is possible
# fast-forward: if main hasn't moved, git just moves the pointer forward

git log --oneline --graph   # shows the merge commit

git branch -d feature/login     # delete branch (safe — already merged)


# =========================================================
# MERGE CONFLICT — what happens when two branches edit the same line
# =========================================================
echo "--- Conflict demo ---"

# Two branches both edit README.md at the same spot
git switch -c branch-a
echo "Version: A" >> README.md
git add README.md && git commit -m "Branch A changes README"

git switch main
echo "Version: B" >> README.md
git add README.md && git commit -m "Branch B changes README"

git merge branch-a || true      # this will conflict

echo ""
echo "Conflict markers in README.md:"
cat README.md
# <<<<<<< HEAD       = your current branch (main)
# =======            = separator
# >>>>>>> branch-a   = incoming branch

# RESOLVE: edit the file to keep what you want, then:
# 1. Edit README.md — remove the markers, keep the right content
python3 -c "
content = open('README.md').read()
# Keep both lines, remove conflict markers
lines = [l for l in content.splitlines()
         if not l.startswith(('<<<', '===', '>>>'))]
open('README.md', 'w').write('\n'.join(lines) + '\n')
" 2>/dev/null || python -c "
content = open('README.md').read()
lines = [l for l in content.splitlines()
         if not l.startswith(('<<<', '===', '>>>'))]
open('README.md', 'w').write('\n'.join(lines) + '\n')
"

# 2. Stage the resolved file
git add README.md

# 3. Complete the merge
git commit -m "Resolve merge conflict in README.md"

git log --oneline --graph

git branch -d branch-a


# =========================================================
# USEFUL BRANCH COMMANDS
# =========================================================
git branch              # list local branches
git branch -a           # list all (including remote)
git branch -v           # with last commit info
git branch --merged     # branches already merged into current

# Rename a branch
git branch -m main production 2>/dev/null || true
git branch -m production main 2>/dev/null || true

cd ~
echo ""
echo "Done! Explore: cd $DEMO_DIR && git log --oneline --graph"

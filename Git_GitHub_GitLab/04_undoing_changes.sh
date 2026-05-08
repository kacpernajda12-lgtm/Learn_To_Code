#!/bin/bash
# 04 - Undoing Changes
# Git gives you many ways to undo mistakes — choose the right one.
#
# SAFETY RULES:
#   - reset --hard and push --force are DESTRUCTIVE — use with caution
#   - prefer revert on shared/public branches (it adds a commit, doesn't rewrite history)
#   - reset is fine on local-only branches

set -e

DEMO_DIR="$HOME/git_demo_04"
rm -rf "$DEMO_DIR"
mkdir "$DEMO_DIR" && cd "$DEMO_DIR"

git init
git config user.name  "Demo"
git config user.email "demo@example.com"

# Setup: a few commits to work with
for i in 1 2 3 4 5; do
    echo "content $i" > "file$i.txt"
    git add "file$i.txt"
    git commit -m "Commit $i: add file$i.txt"
done

echo ""
echo "Starting history:"
git log --oneline


# =========================================================
# RESTORE — discard unstaged changes in the working directory
# =========================================================
echo ""
echo "=== restore (discard working dir changes) ==="
echo "MODIFIED" >> file1.txt
git diff file1.txt                          # shows the change

git restore file1.txt                       # discard — goes back to last commit
git diff file1.txt                          # empty — change is gone

# Restore a staged file back to unstaged
echo "STAGED" >> file2.txt
git add file2.txt
git status                                  # staged
git restore --staged file2.txt             # unstage (keeps the working dir change)
git status                                  # unstaged


# =========================================================
# RESET — move the branch pointer backwards
# Three modes:
#   --soft   move HEAD only (staged changes kept)
#   --mixed  move HEAD + unstage (default)
#   --hard   move HEAD + discard everything (DESTRUCTIVE)
# =========================================================
echo ""
echo "=== reset --soft (undo commit, keep changes staged) ==="
git log --oneline | head -3
git reset --soft HEAD~1                     # undo last commit
git status                                  # file5.txt is staged, not committed
git log --oneline | head -3                 # Commit 5 is gone

# Put it back
git commit -m "Commit 5 (recommitted)"

echo ""
echo "=== reset --mixed (undo commit, keep changes unstaged) ==="
git reset HEAD~1                            # --mixed is the default
git status                                  # file5.txt is unstaged
git add file5.txt && git commit -m "Commit 5 (again)"

echo ""
echo "=== reset --hard (undo commit AND discard changes) ==="
git reset --hard HEAD~1                     # !! file5.txt changes are GONE
git status                                  # clean
git log --oneline

# You can always go back using reflog (see 06_advanced_git.sh)


# =========================================================
# REVERT — safe undo for public/shared branches
# Creates a NEW commit that reverses a previous one.
# Does NOT rewrite history.
# =========================================================
echo ""
echo "=== revert (safe — adds an undo commit) ==="
HASH=$(git log --oneline | grep "Commit 3" | cut -d' ' -f1)
git revert "$HASH" --no-edit               # --no-edit skips the editor

git log --oneline
# You'll see a new "Revert 'Commit 3'" commit — file3.txt is gone but history is intact


# =========================================================
# AMEND — fix the last commit (message or staged files)
# Only use BEFORE pushing — rewrites history
# =========================================================
echo ""
echo "=== amend (fix last commit) ==="
echo "extra content" >> file4.txt
git add file4.txt
git commit --amend --no-edit               # add file4.txt to the previous commit

# Fix commit message only
git commit --amend -m "Commit 4: fixed message + extra content"
git log --oneline | head -3


# =========================================================
# CLEAN — remove untracked files
# =========================================================
echo ""
echo "=== clean ==="
echo "temp" > temp.log
echo "build" > build.out
git status                                  # untracked files

git clean -n                                # dry-run: shows what WOULD be deleted
git clean -f                                # delete untracked files
git status                                  # clean


# =========================================================
# QUICK REFERENCE
# =========================================================
cat << 'EOF'

--- Quick Reference ---
Discard working dir change:    git restore <file>
Unstage a file:                git restore --staged <file>
Undo last commit (keep files): git reset --soft HEAD~1
Undo last commit (discard):    git reset --hard HEAD~1
Undo a pushed commit safely:   git revert <hash>
Fix last commit:               git commit --amend
Remove untracked files:        git clean -fd
EOF

cd ~
echo ""
echo "Done! Explore: cd $DEMO_DIR"

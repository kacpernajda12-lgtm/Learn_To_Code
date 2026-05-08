#!/bin/bash
# 05 - Advanced Git: Rebase, Stash, Cherry-pick, Reflog, Tags

set -e

DEMO_DIR="$HOME/git_demo_05"
rm -rf "$DEMO_DIR"
mkdir "$DEMO_DIR" && cd "$DEMO_DIR"

git init
git config user.name  "Demo"
git config user.email "demo@example.com"

echo "main content" > main.txt
git add main.txt && git commit -m "Initial commit on main"


# =========================================================
# STASH — temporarily shelve uncommitted changes
# Use when you need to switch branches but aren't ready to commit
# =========================================================
echo ""
echo "=== STASH ==="

echo "work in progress" >> main.txt
echo "new untracked" > new_file.txt

git status                          # dirty working tree

git stash push -m "WIP: adding feature" --include-untracked
git status                          # clean — changes are shelved

git stash list                      # stash@{0}: WIP: adding feature

# Come back to your work
git stash pop                       # apply + drop the stash
# or: git stash apply               # apply but keep in stash list

git status                          # changes are back
git checkout main.txt               # discard for demo

# Multiple stashes
git stash push -m "idea A"
git stash push -m "idea B"
git stash list
git stash apply stash@{1}           # apply a specific stash
git stash drop  stash@{1}           # remove it
git stash clear                     # drop all stashes


# =========================================================
# REBASE — replay commits on top of another branch
# Result: cleaner, linear history (no merge commits)
# Rule: NEVER rebase commits that have been pushed to a shared branch
# =========================================================
echo ""
echo "=== REBASE ==="

# Setup: main has moved forward while we were on feature
git switch -c feature/ui
echo "ui component" > ui.py
git add ui.py && git commit -m "Add UI component"
echo "ui style" >> ui.py
git add ui.py && git commit -m "Style UI component"

git switch main
echo "backend update" >> main.txt
git add main.txt && git commit -m "Backend: update logic"
echo "backend fix" >> main.txt
git add main.txt && git commit -m "Backend: fix bug"

echo "Before rebase:"
git log --oneline --graph --all

git switch feature/ui
git rebase main             # replay feature commits on top of current main

echo ""
echo "After rebase:"
git log --oneline --graph --all
# feature/ui commits now sit on top of main's latest commit — clean line

git switch main
git merge feature/ui        # fast-forward merge (no merge commit needed)
git branch -d feature/ui


# =========================================================
# INTERACTIVE REBASE — rewrite, squash, reorder commits
# git rebase -i HEAD~N  (last N commits)
# =========================================================
echo ""
echo "=== Interactive Rebase (simulated with --autosquash) ==="

echo "feature v1" > feature.py
git add feature.py && git commit -m "Add feature v1"
echo "feature v2" >> feature.py
git add feature.py && git commit -m "WIP: tweak feature"
echo "feature v3" >> feature.py
git add feature.py && git commit -m "WIP: another tweak"

# Squash last 3 commits into one non-interactively
git reset --soft HEAD~3
git commit -m "Add feature (squashed 3 commits into 1)"
git log --oneline | head -5


# =========================================================
# CHERRY-PICK — copy a specific commit from another branch
# =========================================================
echo ""
echo "=== CHERRY-PICK ==="

git switch -c hotfix
echo "critical fix" > fix.py
git add fix.py && git commit -m "hotfix: critical security patch"
CHERRY_HASH=$(git log --oneline | head -1 | cut -d' ' -f1)

git switch main
git cherry-pick "$CHERRY_HASH"      # apply just that commit to main
git log --oneline | head -3


# =========================================================
# REFLOG — your safety net
# Records every movement of HEAD — lets you recover "lost" commits
# =========================================================
echo ""
echo "=== REFLOG ==="

echo "important work" > important.txt
git add important.txt && git commit -m "Important work"

git reset --hard HEAD~1             # "lose" the commit

git reflog | head -5
# You can see the hash of the "lost" commit

LOST_HASH=$(git reflog | grep "Important work" | head -1 | cut -d' ' -f1)
git cherry-pick "$LOST_HASH"        # recover it!
git log --oneline | head -3


# =========================================================
# BLAME — who wrote which line, and when
# =========================================================
echo ""
echo "=== BLAME ==="
git blame main.txt


# =========================================================
# BISECT — binary search to find which commit introduced a bug
# =========================================================
echo ""
cat << 'EOF'
=== BISECT (reference — needs manual input) ===
  git bisect start
  git bisect bad              # current commit has the bug
  git bisect good <hash>      # this commit was bug-free
  # Git checks out the midpoint. Test it, then:
  git bisect good             # or: git bisect bad
  # Repeat until git identifies the culprit commit
  git bisect reset            # go back to original state
EOF


# =========================================================
# TAGS — mark a specific commit (e.g., a release)
# =========================================================
echo ""
echo "=== TAGS ==="

git tag v1.0                                    # lightweight tag
git tag -a v1.1 -m "Release 1.1 — bug fixes"   # annotated tag (preferred)
git tag                                         # list all tags
git show v1.1                                   # see tag details

# Push tags to remote (not pushed with normal git push)
# git push origin v1.1
# git push origin --tags    # push ALL tags

git tag -d v1.0             # delete local tag
# git push origin --delete v1.0   # delete remote tag

cd ~
echo ""
echo "Done! Explore: cd $DEMO_DIR"

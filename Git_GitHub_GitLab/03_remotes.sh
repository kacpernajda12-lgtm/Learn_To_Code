#!/bin/bash
# 03 - Remote Repositories
# A remote is a copy of your repo hosted elsewhere (GitHub, GitLab, Bitbucket).
# origin = the conventional name for your main remote.

# NOTE: Commands marked [NEEDS REMOTE] require an actual GitHub/GitLab account.
#       The rest are demonstrated locally using two folders as "remote" and "local".

set -e

REMOTE_DIR="$HOME/git_demo_remote.git"   # bare repo (acts as "server")
LOCAL_DIR="$HOME/git_demo_local"

rm -rf "$REMOTE_DIR" "$LOCAL_DIR"


# =========================================================
# SETUP: create a bare repo to simulate a remote server
# =========================================================
git init --bare "$REMOTE_DIR"
echo "Simulated remote: $REMOTE_DIR"


# =========================================================
# CLONE — download a repo and set up 'origin' automatically
# =========================================================
git clone "$REMOTE_DIR" "$LOCAL_DIR"
cd "$LOCAL_DIR"

git config user.name  "Demo User"
git config user.email "demo@example.com"

git remote -v       # shows: origin -> path/to/remote (fetch + push)


# =========================================================
# PUSH — upload local commits to the remote
# =========================================================
echo "# My App" > README.md
git add README.md
git commit -m "Initial commit"

git push origin main        # push branch 'main' to remote 'origin'
# First time on a new branch:
#   git push -u origin main   (-u sets upstream so future 'git push' works alone)


# =========================================================
# FETCH vs PULL
# fetch = download remote changes, but DON'T merge into your branch
# pull  = fetch + merge (or rebase) in one step
# =========================================================

# Simulate a colleague pushing to the remote
COLLEAGUE_DIR="$HOME/git_demo_colleague"
rm -rf "$COLLEAGUE_DIR"
git clone "$REMOTE_DIR" "$COLLEAGUE_DIR"
cd "$COLLEAGUE_DIR"
git config user.name  "Colleague"
git config user.email "colleague@example.com"
echo "Added by colleague" >> README.md
git add README.md && git commit -m "Colleague: update README"
git push origin main

# Back in our repo
cd "$LOCAL_DIR"

git fetch origin            # download updates, don't merge
git log --oneline origin/main   # see what's on remote
git diff HEAD origin/main       # compare local vs remote

git pull origin main        # fetch + merge (or use: git pull --rebase)

cat README.md               # now has colleague's changes


# =========================================================
# TRACKING BRANCHES
# =========================================================
# After -u, 'git push' and 'git pull' work without arguments
git push -u origin main

git branch -vv              # shows tracking info


# =========================================================
# [NEEDS REMOTE] Real GitHub/GitLab workflow
# =========================================================

# --- Clone from GitHub ---
# git clone https://github.com/user/repo.git
# git clone git@github.com:user/repo.git          (SSH — faster, no password)

# --- Add a remote to an existing local repo ---
# git remote add origin https://github.com/user/repo.git
# git remote add upstream https://github.com/original/repo.git  (for forks)

# --- Push a new branch ---
# git switch -c feature/new-thing
# git push -u origin feature/new-thing

# --- Sync a fork with the original repo ---
# git fetch upstream
# git merge upstream/main
# git push origin main

# --- Remove / rename a remote ---
# git remote remove origin
# git remote rename origin backup


# =========================================================
# USEFUL REMOTE COMMANDS
# =========================================================
git remote show origin      # detailed info about a remote
git remote -v               # list all remotes

cd ~
rm -rf "$COLLEAGUE_DIR"
echo ""
echo "Done! Local repo: $LOCAL_DIR"

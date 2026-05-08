# Git, GitHub & GitLab Tutorial

A practical walkthrough of version control and modern Git hosting workflows.

## How to run the shell scripts

Use **Git Bash** (comes with Git for Windows) or **MSYS2**:

```bash
bash 01_git_basics.sh
```

The `.yml` files are reference configs — copy them into a real project to use them.

## Files

### Git Core

| # | File | Topic |
|---|------|-------|
| 01 | `01_git_basics.sh` | init, add, commit, status, log, .gitignore |
| 02 | `02_branches.sh` | branch, switch, merge, resolve conflicts |
| 03 | `03_remotes.sh` | clone, push, pull, fetch, upstream |
| 04 | `04_undoing_changes.sh` | restore, reset, revert, amend, clean |
| 05 | `05_advanced_git.sh` | stash, rebase, cherry-pick, reflog, blame, tags |

### GitHub & GitLab

| # | File | Topic |
|---|------|-------|
| 06 | `06_github_workflow.sh` | Fork/PR workflow, gh CLI, best practices |
| 07 | `07_gitlab_workflow.sh` | MR workflow, glab CLI, GitLab vs GitHub |
| 08 | `08_github_actions.yml` | CI/CD pipeline with GitHub Actions |
| 09 | `09_gitlab_cicd.yml` | CI/CD pipeline with GitLab CI |
| 10 | `10_git_hooks.sh` | pre-commit, commit-msg, pre-push hooks |

## Key concepts at a glance

| Command | What it does |
|---------|-------------|
| `git init` | Start a new repo |
| `git clone <url>` | Download a remote repo |
| `git add .` | Stage all changes |
| `git commit -m "..."` | Save a snapshot |
| `git push` | Upload commits to remote |
| `git pull` | Download + merge remote changes |
| `git switch -c <name>` | Create and switch to a new branch |
| `git merge <branch>` | Merge a branch into current |
| `git rebase <branch>` | Replay commits on top of another branch |
| `git stash` | Shelve uncommitted work |
| `git log --oneline --graph` | Visual commit history |
| `git reflog` | Full history of HEAD movements |

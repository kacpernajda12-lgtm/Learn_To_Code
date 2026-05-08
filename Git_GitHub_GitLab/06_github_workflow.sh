#!/bin/bash
# 06 - GitHub Workflow
# The standard open-source and team workflow on GitHub.
# Requires: gh CLI (https://cli.github.com) — authenticated with 'gh auth login'

# =========================================================
# FORK → CLONE → BRANCH → PR WORKFLOW
# =========================================================

# Step 1: Fork a repo on GitHub (click "Fork" on the website, or via gh CLI)
# gh repo fork owner/repo --clone=true --remote=true

# Step 2: Clone YOUR fork
# git clone https://github.com/YOUR_USERNAME/repo.git
# cd repo

# Step 3: Add the original repo as 'upstream' (to get future updates)
# git remote add upstream https://github.com/original-owner/repo.git
# git remote -v
# → origin    https://github.com/YOU/repo.git    (your fork)
# → upstream  https://github.com/ORIGINAL/repo.git  (source of truth)

# Step 4: Create a feature branch (NEVER commit directly to main)
# git switch -c feature/my-feature

# Step 5: Make commits
# ... edit files ...
# git add .
# git commit -m "feat: add my feature"

# Step 6: Sync your fork with upstream before pushing
# git fetch upstream
# git rebase upstream/main        # or: git merge upstream/main

# Step 7: Push to YOUR fork
# git push -u origin feature/my-feature

# Step 8: Open a Pull Request
# gh pr create --title "feat: add my feature" --body "Description of changes"


# =========================================================
# GITHUB CLI (gh) — manage GitHub from the terminal
# =========================================================

echo "=== gh CLI Reference ==="

cat << 'EOF'

-- Repositories --
gh repo create NAME --public          create a new repo
gh repo clone USER/REPO               clone a repo
gh repo view                          open repo in browser
gh repo list                          list your repos
gh repo fork OWNER/REPO --clone       fork + clone

-- Pull Requests --
gh pr create                          open a PR (interactive)
gh pr create --title "..." --body "..." --base main
gh pr list                            list open PRs
gh pr view 42                         view PR #42
gh pr checkout 42                     switch to the branch of PR #42
gh pr review 42 --approve             approve a PR
gh pr review 42 --request-changes -b "needs tests"
gh pr merge 42 --squash               merge PR #42 (squash commits)
gh pr merge 42 --rebase               merge with rebase
gh pr close 42                        close without merging

-- Issues --
gh issue create --title "Bug: ..." --body "..."
gh issue list
gh issue view 7
gh issue close 7
gh issue comment 7 --body "Fixed in PR #42"

-- Releases --
gh release create v2.0 --title "Version 2.0" --notes "Changelog..."
gh release list
gh release view v2.0

-- Actions / CI --
gh run list                           list recent workflow runs
gh run view 12345                     view a specific run
gh run watch                          watch the latest run live
gh workflow list                      list all workflows

EOF


# =========================================================
# GITHUB PULL REQUEST BEST PRACTICES
# =========================================================
cat << 'EOF'

=== Pull Request Checklist ===

Title:
  ✓ Short and descriptive (< 72 chars)
  ✓ Use conventional commits prefix: feat|fix|chore|docs|refactor|test
  Example: "feat: add OAuth2 login support"

Description should include:
  ✓ What changed and why
  ✓ How to test it
  ✓ Screenshots for UI changes
  ✓ Related issue: "Closes #42"

Branch hygiene:
  ✓ One feature per branch
  ✓ Keep PRs small (< 400 lines changed when possible)
  ✓ Rebase on main before requesting review
  ✓ Delete the branch after merging

Commit messages (Conventional Commits):
  feat:     a new feature
  fix:      a bug fix
  docs:     documentation only
  style:    formatting, no logic change
  refactor: code change that isn't a bug fix or feature
  test:     adding or fixing tests
  chore:    build process, dependencies, tooling

  Examples:
  feat(auth): add JWT refresh token rotation
  fix(api): handle empty response from /users endpoint
  docs: update README with setup instructions

EOF


# =========================================================
# PROTECTING MAIN BRANCH (GitHub Settings)
# =========================================================
cat << 'EOF'

=== Branch Protection Rules (set in GitHub → Settings → Branches) ===

Recommended for main:
  ✓ Require pull request before merging
  ✓ Require at least 1 approving review
  ✓ Require status checks to pass (CI must be green)
  ✓ Require branches to be up to date before merging
  ✓ Do not allow force pushes
  ✓ Do not allow deletions

EOF

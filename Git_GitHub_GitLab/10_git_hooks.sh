#!/bin/bash
# 10 - Git Hooks
# Hooks are scripts that Git runs automatically at certain events.
# Stored in .git/hooks/ — not committed to the repo by default.
# To share hooks with your team, use a tool like 'pre-commit' (see end of file).

set -e

DEMO_DIR="$HOME/git_demo_hooks"
rm -rf "$DEMO_DIR"
mkdir "$DEMO_DIR" && cd "$DEMO_DIR"

git init
git config user.name  "Demo"
git config user.email "demo@example.com"


# =========================================================
# PRE-COMMIT HOOK — runs before git commit
# If it exits with non-zero, the commit is aborted.
# =========================================================
cat > .git/hooks/pre-commit << 'HOOK'
#!/bin/bash
echo "[pre-commit] Running checks..."

# 1. Reject files with debug print statements
if git diff --cached --name-only | xargs grep -l "print('DEBUG" 2>/dev/null; then
    echo "ERROR: Remove debug print statements before committing."
    exit 1
fi

# 2. Reject TODO/FIXME comments on staged Python files
STAGED_PY=$(git diff --cached --name-only | grep '\.py$' || true)
if [ -n "$STAGED_PY" ]; then
    if echo "$STAGED_PY" | xargs grep -n "FIXME" 2>/dev/null; then
        echo "ERROR: Resolve FIXME comments before committing."
        exit 1
    fi
fi

# 3. Run linter if available
if command -v ruff &>/dev/null && [ -n "$STAGED_PY" ]; then
    echo "$STAGED_PY" | xargs ruff check --quiet || {
        echo "ERROR: Linting failed. Run 'ruff check --fix .' to auto-fix."
        exit 1
    }
fi

echo "[pre-commit] All checks passed."
exit 0
HOOK
chmod +x .git/hooks/pre-commit


# Test the hook: commit a clean file — should succeed
echo "clean code" > app.py
git add app.py && git commit -m "Clean commit"

# Test the hook: commit a file with FIXME — should be blocked
echo "# FIXME: remove this" >> app.py
git add app.py
git commit -m "Bad commit" 2>&1 || echo "(commit blocked as expected)"

git checkout app.py   # discard


# =========================================================
# COMMIT-MSG HOOK — validate commit message format
# =========================================================
cat > .git/hooks/commit-msg << 'HOOK'
#!/bin/bash
# Enforce Conventional Commits format:
# type(scope): description
# types: feat|fix|docs|style|refactor|test|chore|ci|build|perf

MSG=$(cat "$1")
PATTERN="^(feat|fix|docs|style|refactor|test|chore|ci|build|perf)(\(.+\))?: .{1,72}"

if ! echo "$MSG" | grep -qE "$PATTERN"; then
    echo ""
    echo "ERROR: Commit message doesn't follow Conventional Commits format."
    echo "Expected:  type(scope): description"
    echo "Example:   feat(auth): add JWT login endpoint"
    echo "Types:     feat fix docs style refactor test chore ci build perf"
    echo ""
    echo "Your message: $MSG"
    exit 1
fi
exit 0
HOOK
chmod +x .git/hooks/commit-msg

# Test: valid message
echo "more code" >> app.py
git add app.py
git commit -m "feat(app): add more code"

# Test: invalid message (blocked)
echo "extra" >> app.py
git add app.py
git commit -m "updated stuff" 2>&1 || echo "(commit blocked as expected)"
git checkout app.py


# =========================================================
# PRE-PUSH HOOK — runs before git push
# =========================================================
cat > .git/hooks/pre-push << 'HOOK'
#!/bin/bash
echo "[pre-push] Running tests before push..."

# Run test suite — abort push if tests fail
if command -v pytest &>/dev/null; then
    pytest --tb=short -q || {
        echo "ERROR: Tests failed. Fix them before pushing."
        exit 1
    }
fi

echo "[pre-push] Tests passed. Pushing."
exit 0
HOOK
chmod +x .git/hooks/pre-push


# =========================================================
# PREPARE-COMMIT-MSG — auto-populate commit message
# =========================================================
cat > .git/hooks/prepare-commit-msg << 'HOOK'
#!/bin/bash
# Prepend the branch name to the commit message
BRANCH=$(git symbolic-ref --short HEAD 2>/dev/null || echo "")
MSG_FILE="$1"

# Only add branch prefix if it looks like a ticket number (e.g. JIRA-123)
if echo "$BRANCH" | grep -qE '^[A-Z]+-[0-9]+'; then
    sed -i "1s/^/[$BRANCH] /" "$MSG_FILE"
fi
HOOK
chmod +x .git/hooks/prepare-commit-msg


# =========================================================
# POST-COMMIT HOOK — runs after a successful commit
# =========================================================
cat > .git/hooks/post-commit << 'HOOK'
#!/bin/bash
echo "[post-commit] Commit recorded: $(git log -1 --oneline)"
# Could send a notification, update a changelog, etc.
HOOK
chmod +x .git/hooks/post-commit


echo ""
echo "Done! Hooks installed in $DEMO_DIR/.git/hooks/"
ls -la "$DEMO_DIR/.git/hooks/"


# =========================================================
# PRE-COMMIT FRAMEWORK — share hooks with your team
# pip install pre-commit
# =========================================================
cat << 'EOF'

=== .pre-commit-config.yaml (place in repo root) ===

repos:
  - repo: https://github.com/pre-commit/pre-commit-hooks
    rev: v4.5.0
    hooks:
      - id: trailing-whitespace
      - id: end-of-file-fixer
      - id: check-yaml
      - id: check-merge-conflict
      - id: detect-private-key

  - repo: https://github.com/astral-sh/ruff-pre-commit
    rev: v0.3.0
    hooks:
      - id: ruff
        args: [--fix]

  - repo: https://github.com/psf/black
    rev: 24.2.0
    hooks:
      - id: black

# Install hooks: pre-commit install
# Run manually:  pre-commit run --all-files
# Skip once:     git commit --no-verify -m "..."

EOF

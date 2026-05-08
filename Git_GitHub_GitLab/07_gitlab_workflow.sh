#!/bin/bash
# 07 - GitLab Workflow
# GitLab is similar to GitHub but with stronger built-in CI/CD.
# Key difference: Pull Request → Merge Request (MR)
# Requires: glab CLI (https://gitlab.com/gitlab-org/cli) — or use the web UI

# =========================================================
# GITLAB CLI (glab) — manage GitLab from the terminal
# =========================================================

echo "=== glab CLI Reference ==="

cat << 'EOF'

-- Authentication --
glab auth login                         authenticate with GitLab
glab auth status                        check auth status

-- Repositories --
glab repo create NAME --public          create a new project
glab repo clone GROUP/PROJECT           clone a project
glab repo view                          open project in browser
glab repo fork NAMESPACE/PROJECT        fork a project

-- Merge Requests (= GitHub Pull Requests) --
glab mr create                          interactive MR creation
glab mr create --title "feat: ..." \
  --description "..." \
  --source-branch feature/x \
  --target-branch main
glab mr list                            list open MRs
glab mr view 5                          view MR #5
glab mr checkout 5                      switch to the MR branch
glab mr approve 5                       approve an MR
glab mr merge 5                         merge MR #5
glab mr close 5                         close without merging
glab mr diff 5                          show the diff

-- Issues --
glab issue create --title "Bug: ..." --description "..."
glab issue list
glab issue view 3
glab issue close 3
glab issue note 3 --message "Fixed in MR !5"

-- CI/CD Pipelines --
glab pipeline list                      list recent pipelines
glab pipeline view 9876                 view pipeline details
glab pipeline run                       trigger a pipeline manually
glab ci view                            watch the current branch pipeline live
glab ci trace JOB_ID                    stream logs of a specific job

-- Releases --
glab release create v1.0 --name "v1.0" --notes "First release"
glab release list

EOF


# =========================================================
# GITLAB MR WORKFLOW (same steps as GitHub PR)
# =========================================================
cat << 'EOF'

=== Merge Request Workflow ===

1. Create a feature branch
   git switch -c feature/my-feature

2. Make and commit your changes
   git add .
   git commit -m "feat: my feature"

3. Push to GitLab
   git push -u origin feature/my-feature

4. GitLab prints a URL to create an MR — click it, or:
   glab mr create --fill    (auto-fills from last commit message)

5. The MR triggers the CI/CD pipeline automatically

6. Reviewer approves → pipeline passes → merge

EOF


# =========================================================
# GITLAB-SPECIFIC FEATURES
# =========================================================
cat << 'EOF'

=== GitLab Features Not in GitHub (free tier) ===

Protected Branches:
  Settings → Repository → Protected Branches
  - Require MR before merging
  - Require approvals (Approvals rules)
  - Only maintainers can push directly

Environments & Deployments:
  Built-in environment tracking (dev, staging, production)
  Deployments are linked directly to CI/CD jobs

Container Registry:
  Each project gets a built-in Docker registry
  docker login registry.gitlab.com
  docker push registry.gitlab.com/group/project:tag

GitLab Runners:
  Shared runners are free on gitlab.com
  Self-host runners for private infra:
  gitlab-runner register

Code Owners (CODEOWNERS file):
  # Require specific people to review certain files
  /backend/  @backend-team
  *.sql      @dba-team

Snippets:
  Like GitHub Gists — share code without a full project
  glab snippet create --title "my script" main.sh

EOF


# =========================================================
# GITLAB VS GITHUB TERMINOLOGY
# =========================================================
cat << 'EOF'

=== Terminology Comparison ===

GitHub                  GitLab
---------               ---------
Repository              Project
Pull Request (PR)       Merge Request (MR)
Actions                 CI/CD Pipelines
Packages                Container Registry / Package Registry
Gists                   Snippets
Organizations           Groups
Teams                   Subgroups
GitHub Pages            GitLab Pages
Checks                  Pipeline Jobs
Branch protection       Protected Branches

EOF

#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

REPO_NAME="revision-cpp-14-days"

command -v git >/dev/null || { echo "Install git (e.g. sudo pacman -S git)"; exit 1; }
command -v gh >/dev/null || { echo "Install GitHub CLI (e.g. sudo pacman -S github-cli)"; exit 1; }

if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  git init -b main
fi

git add -A

if ! git rev-parse HEAD >/dev/null 2>&1; then
  git commit -m "$(cat <<'EOF'
Initial commit: 14-day modern C++14 exercise track.

EOF
)"
elif [[ -n "$(git status --porcelain)" ]]; then
  git commit -m "Update revision-cpp-14-days"
fi

if git remote get-url origin >/dev/null 2>&1; then
  echo "Remote origin already set: $(git remote get-url origin)"
  git push -u origin main
else
  gh repo create "$REPO_NAME" --public --source=. --remote=origin --push
fi

echo "Done. Open with: gh repo view --web"

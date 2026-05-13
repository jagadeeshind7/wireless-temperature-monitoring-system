# GitHub Repository Setup Guide

This guide explains how to push this project to GitHub from your MacBook Air terminal.

## Step 1 — One-time Git Configuration

Open Terminal (`Cmd + Space` → type Terminal):

```bash
git config --global user.name "Your Name"
git config --global user.email "your@email.com"
```

## Step 2 — Create a New Repository on GitHub

1. Go to [github.com](https://github.com) and sign in.
2. Click the **+** icon → **New repository**.
3. Name it: `wireless-temperature-monitor`
4. Set visibility to **Public**.
5. Do NOT add README, .gitignore, or licence (we already have them).
6. Click **Create repository**.
7. Copy the repository URL shown on screen.

## Step 3 — Initialize and Push from Terminal

```bash
# Navigate to the project folder
cd ~/path/to/wtms-repo

# Initialize git
git init -b main

# Stage all files
git add .

# First commit
git commit -m "Add: Initial commit — Wireless Temperature Monitoring System"

# Link to your GitHub repo
git remote add origin https://github.com/YOUR_USERNAME/wireless-temperature-monitor.git

# Push
git push -u origin main
```

## Step 4 — Future Updates

Every time you edit files and want to save changes to GitHub:

```bash
git add .
git commit -m "Update: describe what changed"
git push
```

## Step 5 — Making the README Look Great

GitHub automatically renders your `README.md` as the project homepage.

To add a badge at the top of your README:

```markdown
![Arduino](https://img.shields.io/badge/Arduino-UNO-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Active-brightgreen)
```

## Naming Conventions Used in This Project

| Type | Convention | Example |
|---|---|---|
| Markdown files | lowercase-hyphenated | `pin-connections.md` |
| Arduino sketches | camelCase folder name | `transmitter.ino` |
| Folders | lowercase-hyphenated | `docs/upgrades/` |
| Commit messages | Prefix + short description | `Add: LoRa upgrade guide` |
| Branch names | feature/short-description | `feature/oled-display` |

## Repository Structure

```
wireless-temperature-monitor/
│
├── README.md                         ← GitHub project homepage
├── LICENSE                           ← MIT licence
├── .gitignore                        ← Files excluded from Git
├── CONTRIBUTING.md                   ← How to contribute
├── GITHUB-SETUP.md                   ← This file
├── libraries-required.txt            ← All required libraries listed
│
├── src/                              ← All source code
│   ├── transmitter/
│   │   └── transmitter.ino
│   └── receiver/
│       └── receiver.ino
│
├── hardware/                         ← Hardware documentation
│   ├── components-list.md
│   └── pin-connections.md
│
├── docs/                             ← All documentation
│   ├── architecture.md
│   ├── working-flow.md
│   ├── specifications.md
│   ├── troubleshooting.md
│   │
│   ├── simulation/                   ← Simulation guides
│   │   ├── simulation-guide.md
│   │   └── wokwi-link.md
│   │
│   └── upgrades/                     ← Future upgrade guides
│       ├── future-improvements.md
│       ├── esp32-upgrade.md
│       ├── lora-upgrade.md
│       └── cloud-integration.md
│
└── images/                           ← Project photos and diagrams
    └── (place your project images here)
```

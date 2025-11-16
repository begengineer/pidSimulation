# GitHub に SSH で `git push` できるようにする手順まとめ

## 1. SSH 鍵の存在を確認
ls ~/.ssh

## 2. sshのカギを作成
もしなかった場合(ed25519とかに記載がないとき)
ssh-keygen -t ed25519 -C "GitHubに登録しているメールアドレス"

## 3. 公開鍵を GitHub に登録

公開鍵を表示：
cat ~/.ssh/id_ed25519.pub

GitHub 側での操作：
右上アイコン → Settings
SSH and GPG keys
New SSH key
Title：任意（例：cD-PC）
Key：id_ed25519.pub の内容を貼り付け
Add SSH key



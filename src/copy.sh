#!/bin/bash

SRC_PATH="/home/gitlab-runner/builds/ouGLtEgG/0/students/DO6_CICD.ID_356283/nettiery_student.21_school.ru/DO6_CICD-1/src"
DEST_PATH="/usr/local/bin"
REMOTE_USER="olga"
REMOTE_HOST="10.10.0.2"

scp "$SRC_PATH/cat/s21_cat" "$REMOTE_USER@$REMOTE_HOST:$DEST_PATH"

scp "$SRC_PATH/grep/s21_grep" "$REMOTE_USER@$REMOTE_HOST:$DEST_PATH"

ssh "$REMOTE_USER@$REMOTE_HOST" ls -lah "$DEST_PATH"

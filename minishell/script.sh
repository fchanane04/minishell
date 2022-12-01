#!/bin/bash
while [ 1 ]
do 
    leaks minishell | grep "leaks for"
    sleep 1
done
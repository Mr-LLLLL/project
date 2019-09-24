#!/bin/bash

if [ $# -eq 0 ];then
    echo "please input the argument: "
    echo "  start    -----> start the nginx"
    echo "  stop     -----> stop  the nginx"
    echo "  reload   -----> reload the nginx"
    exit 1
fi

case $1 in
    start)
        sudo /usr/local/nginx/sbin/nginx 
        if [ $? -eq 0 ];then
            echo "nginx started successly ..."
        else
            echo "nginx start failed ..."
        fi
        ;;
    stop)
        sudo /usr/local/nginx/sbin/nginx -s quit
        if [ $? -eq 0 ];then
            echo "nginx stop successly ..."
        else
            echo "nginx stop failed ..."
        fi
        ;;
    reload)
        sudo /usr/local/nginx/sbin/nginx -s reload
        if [ $? -eq 0 ];then
            echo "nginx reload successly ..."
        else
            echo "nginx reload failed ..."
        fi
        ;;
    *)
        echo "do nothing ..."
        ;;
esac


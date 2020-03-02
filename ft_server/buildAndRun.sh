docker build -t ft_server .
docker rm ft_server
docker run -ti -p 80:80 -p 443:443 --name ft_server ft_server
FROM ubuntu:22.04

RUN useradd -m ctf

COPY ./start.sh /start.sh

RUN chmod +x /start.sh

COPY ./bin/ /home/ctf

RUN chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf && \
    chmod 740 /home/ctf/flag

CMD ["/start.sh"]

EXPOSE 12345

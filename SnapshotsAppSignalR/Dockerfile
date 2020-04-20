#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/core/aspnet:3.1.3-buster-slim-arm32v7 AS base

WORKDIR /app
EXPOSE 80
EXPOSE 443

ADD Tools /app
#RUN ls
RUN chmod +x install_dependencies.sh
RUN ./install_dependencies.sh

FROM mcr.microsoft.com/dotnet/core/sdk:3.1-bionic-arm32v7 AS build 
WORKDIR /src
COPY ["Server/SnapshotsAppSignalR.Server.csproj", "Server/"]
COPY ["Shared/SnapshotsAppSignalR.Shared.csproj", "Shared/"]
COPY ["Client/SnapshotsAppSignalR.Client.csproj", "Client/"]
#ARG buildtime_os=linux
#ARG buildtime_cpu=x64
#ENV PROTOBUF_TOOLS_OS=$buildtime_os
#ENV PROTOBUF_TOOLS_CPU=$buildtime_cpu
#ENV PROTOBUF_PROTOC=/data/protoc
#COPY ["/usr/bin/protoc", "/data/protoc"]
RUN dotnet restore "Server/SnapshotsAppSignalR.Server.csproj"
COPY . .
WORKDIR "/src/Server"
RUN dotnet build "SnapshotsAppSignalR.Server.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "SnapshotsAppSignalR.Server.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "SnapshotsAppSignalR.Server.dll"]
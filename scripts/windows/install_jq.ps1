if($env:APPVEYOR_REPO_TAG -eq 'true') {
    Start-FileDownload https://github.com/stedolan/jq/releases/download/jq-1.5/jq-win64.exe
}

# Script to remove problem folders created by the previous script
$destRoot = "C:\Users\mmini\Documents\CompetitiveProgramming"

# Get all judge directories
$judgeDirs = Get-ChildItem -Path $destRoot -Directory | Where-Object { 
    $_.Name -match '^(codeforces|atcoder|spoj|uva|poj|kattis|dmoj|eolymp|gym|hackerrank|hdu|lightoj|ojuz|sgu|topcoder|universaloj|ural|usaco|uvalive|yosupo|zoj|cses|libreoj|openj_bailian)$'
}

foreach ($judgeDir in $judgeDirs) {
    # Get all problem directories in this judge that might have been created
    $problemDirs = Get-ChildItem -Path $judgeDir.FullName -Directory
    
    foreach ($problemDir in $problemDirs) {
        $problemName = $problemDir.Name
        $problemFile = Join-Path -Path $problemDir.FullName -ChildPath "$problemName.cpp"
        
        # If this is a generated problem directory with a matching file inside
        if (Test-Path -Path $problemFile) {
            # Copy the file to the judge directory
            $destFilePath = Join-Path -Path $judgeDir.FullName -ChildPath "$problemName.cpp"
            Write-Host "Moving $problemName.cpp to judge directory"
            Copy-Item -Path $problemFile -Destination $destFilePath -Force
            
            # Remove the problem directory and its contents
            Write-Host "Removing directory: $($problemDir.FullName)"
            Remove-Item -Path $problemDir.FullName -Recurse -Force
        }
    }
}

Write-Host "Cleanup complete!" 
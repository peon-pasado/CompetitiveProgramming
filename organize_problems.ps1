# Script to organize problems from _threat_-ac into judge-specific directories
$sourceRoot = "C:\Users\mmini\Documents\CompetitiveProgramming\_threat_-ac"
$destRoot = "C:\Users\mmini\Documents\CompetitiveProgramming"

# Get all judge directories
$judgeDirs = Get-ChildItem -Path $sourceRoot -Directory

foreach ($judgeDir in $judgeDirs) {
    $judgeName = $judgeDir.Name.ToLower()
    $destJudgeDir = Join-Path -Path $destRoot -ChildPath $judgeName
    
    # Create judge directory if it doesn't exist
    if (-not (Test-Path -Path $destJudgeDir)) {
        Write-Host "Creating judge directory: $judgeName"
        New-Item -Path $destJudgeDir -ItemType Directory | Out-Null
    }
    
    # Get all problem directories in this judge
    $problemDirs = Get-ChildItem -Path $judgeDir.FullName -Directory
    
    foreach ($problemDir in $problemDirs) {
        $problemName = $problemDir.Name.ToLower()
        $destProblemDir = Join-Path -Path $destJudgeDir -ChildPath $problemName
        
        # Create problem directory if it doesn't exist
        if (-not (Test-Path -Path $destProblemDir)) {
            Write-Host "Creating problem directory: $judgeName/$problemName"
            New-Item -Path $destProblemDir -ItemType Directory | Out-Null
        }
        
        # Find all solution files in the problem directory
        $solutionFiles = Get-ChildItem -Path $problemDir.FullName -File -Filter "*.cpp"
        
        # Track the best (fastest) solution
        $bestSolution = $null
        $bestTime = [System.Double]::MaxValue
        
        foreach ($solutionFile in $solutionFiles) {
            # Parse time from filename (format: ID_AC_Xms_YkB.cpp)
            if ($solutionFile.Name -match "_AC_(\d+)ms_") {
                $time = [double]$matches[1]
                
                # If this is faster than our current best, update
                if ($time -lt $bestTime) {
                    $bestTime = $time
                    $bestSolution = $solutionFile
                }
            }
        }
        
        # If we found a best solution, copy it to the destination
        if ($bestSolution -ne $null) {
            $destFileName = "$problemName.cpp"
            $destFilePath = Join-Path -Path $destProblemDir -ChildPath $destFileName
            
            Write-Host "Copying best solution for $judgeName/$problemName (${bestTime}ms)"
            Copy-Item -Path $bestSolution.FullName -Destination $destFilePath -Force
        }
    }
}

Write-Host "Organization complete!" 
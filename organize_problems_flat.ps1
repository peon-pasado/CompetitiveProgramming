# Script to organize problems from _threat_-ac into judge-specific directories (flat structure)
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
        
        # Check if this is already in an existing directory structure
        $existingDir = Join-Path -Path $destJudgeDir -ChildPath $problemName
        $isExistingProblemDir = Test-Path -Path $existingDir -PathType Container
        
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
            if ($isExistingProblemDir) {
                # If directory already exists, place it inside
                $destFileName = "$problemName.cpp"
                $destFilePath = Join-Path -Path $existingDir -ChildPath $destFileName
                Write-Host "Copying to existing directory: $judgeName/$problemName (${bestTime}ms)"
            } else {
                # Otherwise place it directly in the judge directory
                $destFileName = "$problemName.cpp"
                $destFilePath = Join-Path -Path $destJudgeDir -ChildPath $destFileName
                Write-Host "Copying to judge directory: $judgeName/$destFileName (${bestTime}ms)"
            }
            
            Copy-Item -Path $bestSolution.FullName -Destination $destFilePath -Force
        }
    }
}

Write-Host "Organization complete!" 
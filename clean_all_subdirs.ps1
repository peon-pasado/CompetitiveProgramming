# Script para limpiar todas las carpetas de problemas en todos los directorios de jueces
$judgeDirectories = @(
    "codechef", "atcoder", "codeforces", "spoj", "uva", "poj", "kattis", "dmoj", 
    "eolymp", "gym", "hackerrank", "hdu", "lightoj", "ojuz", "sgu", "topcoder", 
    "universaloj", "ural", "usaco", "uvalive", "yosupo", "zoj", "cses", "libreoj", 
    "openj_bailian", "timus", "toki", "szkoput", "project_euler", "live_archive",
    "oj.uz", "infoarena", "e-olymp", "dunjudge", "csacademy", "camp", "balkan", "A2OJ",
    "baekjoon", "LOJ", "tju", "wcipeg", "yandex"
)

$baseDir = "C:\Users\mmini\Documents\CompetitiveProgramming"

foreach ($judge in $judgeDirectories) {
    $judgePath = Join-Path -Path $baseDir -ChildPath $judge
    
    # Verificar si el directorio del juez existe
    if (Test-Path -Path $judgePath -PathType Container) {
        Write-Host "Procesando directorio: $judge"
        
        # Obtener todos los subdirectorios
        $problemDirs = Get-ChildItem -Path $judgePath -Directory
        
        foreach ($problemDir in $problemDirs) {
            $problemName = $problemDir.Name.ToLower()
            Write-Host "  Procesando problema: $problemName"
            
            # Buscar todos los archivos .cpp en el subdirectorio
            $files = Get-ChildItem -Path $problemDir.FullName -Recurse -Filter "*.cpp"
            
            # Si hay archivos .cpp, seleccionar el mejor y copiarlo al directorio principal
            if ($files.Count -gt 0) {
                # Obtener el archivo .cpp más reciente (usaremos este como "mejor")
                $bestFile = $files | Sort-Object LastWriteTime -Descending | Select-Object -First 1
                
                # Construir el nombre del archivo destino
                $destFileName = "$problemName.cpp"
                $destPath = Join-Path -Path $judgePath -ChildPath $destFileName
                
                # Copiar el archivo al directorio principal
                Write-Host "    Copiando $($bestFile.Name) a $destFileName"
                Copy-Item -Path $bestFile.FullName -Destination $destPath -Force
            }
            
            # Eliminar el subdirectorio
            Write-Host "    Eliminando directorio: $($problemDir.FullName)"
            Remove-Item -Path $problemDir.FullName -Recurse -Force
        }
    }
}

Write-Host "Proceso completado. Todos los subdirectorios de problemas han sido eliminados." 
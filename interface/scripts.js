function mountMatrix(d) {

    const matrix = document.getElementById('matrix');
    const matrixWidth = 30 * d;

    matrix.style.width = `${matrixWidth}px`;
    matrix.style.height = `${matrixWidth}px`;

    for (let i = 0; i < d; i++) {
        for (let j = 0; j < d; j++) {
            const cell = document.createElement('input');
            cell.id = `${i},${j}`;
            cell.classList.add('cell');
            cell.type = 'number';
            matrix.appendChild(cell);
        }   
    }
}

mountMatrix(2);
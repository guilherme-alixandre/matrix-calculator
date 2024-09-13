let dimension = 2;

function mountMatrix(d) {

    const oldMatrix = document.getElementById('matrix');
    if(oldMatrix) oldMatrix.remove();

    const matrix = document.createElement('div');
    matrix.id = 'matrix';

    for (let i = 0; i < d; i++) {

        const row = document.createElement('div');
        row.id = 'row';
        row.style.flexBasis = '100%';

        for (let j = 0; j < d + 1; j++) {
            const cell = document.createElement('input');
            cell.id = `${i},${j}`;
            cell.classList.add('cell');
            cell.type = 'number';
            
            if(j == d) {
                const equal = document.createElement('span');
                equal.textContent = '=';
                row.appendChild(equal);
            } else if (j <= d) {
                
                cell.placeholder = `X${j + 1}`;
            }
            
            row.appendChild(cell);
        }   

        matrix.appendChild(row);
    }

    const container = document.getElementById('container');
    container.appendChild(matrix)
}

function changeBackgroundColor () {
    const r = dimension == 2 ? 255 : Math.floor(Math.random() * 256); 
    const g = dimension == 2 ? 255 : Math.floor(Math.random() * 256);
    const b = dimension == 2 ? 255 : Math.floor(Math.random() * 256);
    document.body.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;
}

function increase(){
    dimension++;
    mountMatrix(dimension);
    changeBackgroundColor();
}

function decrease(){
    if (dimension - 1 > 1) {
        dimension--;
        mountMatrix(dimension);
        changeBackgroundColor();
    }
}

mountMatrix(dimension);
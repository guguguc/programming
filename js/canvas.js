const BYTES_PER_PIXEL = 4

function indexForPixel(imageData, width, x, y)
{
} 

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext('2d');
const arr = new Uint8ClampedArray(40000);

canvas.height = 50;
for (let i= 0; i < arr.length; i += 4) {
    arr[i + 0] = 128;
    arr[i + 1] = 128;
    arr[i + 2] = 128;
    arr[i + 3] = 255;
}

let imageData = new ImageData(arr, 400);
console.log("hello, word");
ctx.putImageData(imageData, 1, 10);
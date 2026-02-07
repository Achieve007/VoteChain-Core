document.addEventListener('DOMContentLoaded', function() {
    const canvas = document.getElementById('heartCanvas');
    const ctx = canvas.getContext('2d');
    
    // Set canvas size
    canvas.width = 500;
    canvas.height = 400;
    
    // Draw the heart equation
    drawHeart(ctx, canvas.width, canvas.height);
    
    // Add animation
    let k = 4.11;
    let growing = false;
    
    setInterval(() => {
        if (growing) {
            k += 0.02;
            if (k >= 4.5) growing = false;
        } else {
            k -= 0.02;
            if (k <= 3.8) growing = true;
        }
        
        // Clear and redraw
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        drawHeart(ctx, canvas.width, canvas.height, k);
    }, 50);
});

function drawHeart(ctx, width, height, k = 10) {
    ctx.save();
    
    // Center and scale
    const centerX = width / 2;
    const centerY = height / 2;
    const scale = 50;
    
    ctx.translate(centerX, centerY);
    ctx.scale(1, -1); // Flip Y axis
    
    // Draw axes
    ctx.strokeStyle = 'rgba(200, 200, 200, 0.5)';
    ctx.lineWidth = 1;
    
    // X axis
    ctx.beginPath();
    ctx.moveTo(-centerX, 0);
    ctx.lineTo(centerX, 0);
    ctx.stroke();
    
    // Y axis
    ctx.beginPath();
    ctx.moveTo(0, -centerY);
    ctx.lineTo(0, centerY);
    ctx.stroke();
    
    // Draw heart
    ctx.strokeStyle = '#e74c3c';
    ctx.fillStyle = 'rgba(231, 76, 60, 0.2)';
    ctx.lineWidth = 2;
    
    ctx.beginPath();
    
    const steps = 1000;
    const xMin = -Math.sqrt(3);
    const xMax = Math.sqrt(3);
    
    for (let i = 0; i <= steps; i++) {
        const x = xMin + (xMax - xMin) * (i / steps);
        const y = Math.pow(Math.abs(x), 2/3) + 0.9 * Math.sin(k * x) * Math.sqrt(3 - x * x);
        
        const plotX = x * scale;
        const plotY = y * scale;
        
        if (i === 0) {
            ctx.moveTo(plotX, plotY);
        } else {
            ctx.lineTo(plotX, plotY);
        }
    }
    
    // Mirror for the other side
    for (let i = steps; i >= 0; i--) {
        const x = xMin + (xMax - xMin) * (i / steps);
        const y = -Math.pow(Math.abs(x), 2/3) - 0.9 * Math.sin(k * x) * Math.sqrt(3 - x * x);
        
        const plotX = x * scale;
        const plotY = y * scale;
        ctx.lineTo(plotX, plotY);
    }
    
    ctx.closePath();
    ctx.fill();
    ctx.stroke();
    
    ctx.restore();
}
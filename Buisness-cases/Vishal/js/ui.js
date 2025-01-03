// Handle code tabs
const tabButtons = document.querySelectorAll('.tab-button');
const codeBlocks = document.querySelectorAll('.code-block');

tabButtons.forEach(button => {
    button.addEventListener('click', () => {
        // Remove active class from all buttons and code blocks
        tabButtons.forEach(btn => btn.classList.remove('active'));
        codeBlocks.forEach(block => block.classList.remove('active'));
        
        // Add active class to clicked button and corresponding code block
        button.classList.add('active');
        const tabId = button.getAttribute('data-tab');
        document.getElementById(`${tabId}-code`).classList.add('active');
    });
});
function handleIntersection(entries, observer) {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('visible');
            observer.unobserve(entry.target);
        }
    });
}

function initializeAnimations() {
    const observer = new IntersectionObserver(handleIntersection, {
        threshold: 0.1
    });

    document.querySelectorAll('.slide-in').forEach(element => {
        observer.observe(element);
    });
}

document.addEventListener('DOMContentLoaded', initializeAnimations);
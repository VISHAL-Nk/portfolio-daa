class AnimationManager {
    constructor() {
        this.observeElements();
    }

    observeElements() {
        const observer = new IntersectionObserver(
            (entries) => {
                entries.forEach(entry => {
                    if (entry.isIntersecting) {
                        entry.target.classList.add('visible');
                    }
                });
            },
            { threshold: 0.1 }
        );

        document.querySelectorAll('.slide-up').forEach(el => observer.observe(el));
    }

    static addScrollAnimation(element) {
        element.classList.add('slide-up');
    }
}

new AnimationManager();
class PortfolioApp {
    constructor() {
        this.reflectionSection = document.getElementById('reflection');
        this.init();
    }

    init() {
        this.loadReflectionContent();
    }

    loadReflectionContent() {
        const content = reflectionData.map(section => `
            <div class="info-card slide-up">
                <h2>${section.title}</h2>
                <ul>
                    ${section.items.map(item => `
                        <li>
                            <i class="icon-chevron-right"></i>
                            <span>${item}</span>
                        </li>
                    `).join('')}
                </ul>
            </div>
        `).join('');

        this.reflectionSection.innerHTML = content;
        
        // Initialize animations for new content
        document.querySelectorAll('.slide-up').forEach(el => {
            AnimationManager.addScrollAnimation(el);
        });
    }
}

new PortfolioApp();
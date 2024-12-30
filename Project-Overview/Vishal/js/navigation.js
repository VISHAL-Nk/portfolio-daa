class Navigation {
    constructor() {
        this.buttons = document.querySelectorAll('.nav-btn');
        this.sections = document.querySelectorAll('.section');
        this.init();
    }

    init() {
        this.buttons.forEach(button => {
            button.addEventListener('click', () => this.switchSection(button));
        });
    }

    switchSection(button) {
        const sectionId = button.dataset.section;
        
        // Update buttons
        this.buttons.forEach(btn => btn.classList.remove('active'));
        button.classList.add('active');
        
        // Update sections
        this.sections.forEach(section => {
            section.classList.remove('active');
            if (section.id === sectionId) {
                section.classList.add('active');
            }
        });
    }
}

new Navigation();
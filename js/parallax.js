// Parallax effect
export const initParallax = () => {
    const landingSection = document.querySelector('.landing-section');
    
    window.addEventListener('scroll', () => {
      const scrolled = window.pageYOffset;
      if (landingSection) {
        landingSection.style.backgroundPosition = `center ${scrolled * 0.5}px`;
      }
    });
  };
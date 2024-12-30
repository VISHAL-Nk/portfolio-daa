import { fadeInElement, createObserver } from './js/animations.js';
import { initMobileMenu, initSmoothScroll } from './js/navigation.js';
import { initParallax } from './js/parallax.js';

document.addEventListener('DOMContentLoaded', () => {
  // Initialize navigation
  initMobileMenu();
  initSmoothScroll();
  initParallax();

  // Set up animations
  const observer = createObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        fadeInElement(entry.target);
      }
    });
  });

  // Observe cards
  document.querySelectorAll('.topic-card, .app-card').forEach((card, index) => {
    card.style.animationDelay = `${index * 0.2}s`;
    observer.observe(card);
  });
}); 
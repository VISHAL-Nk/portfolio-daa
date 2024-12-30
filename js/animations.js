// Animation utilities
export const fadeInElement = (element, delay = 0) => {
    element.style.animationDelay = `${delay}s`;
    element.classList.add('visible');
  };
  
  export const createObserver = (callback) => {
    return new IntersectionObserver(callback, {
      threshold: 0.2,
      rootMargin: '0px'
    });
  };
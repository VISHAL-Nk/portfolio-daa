export function createTeamCard(member, index) {
    const card = document.createElement('a');
    
    // Set different links for each team member
    switch(index) {
        case 0:
            card.href = 'https://sites.google.com/kletech.ac.in/daaportfoliobdiv218/home';
            break;
        case 1:
            card.href = 'https://sites.google.com/kletech.ac.in/daaportfolio227/graph-algorithm';
            break;
        case 2:
            card.href = 'https://sites.google.com/kletech.ac.in/daa-portfolio-227/home';
            break;
        case 3:
            card.href = 'Vishal/index.html';
            break;
        default:
            card.href = '#';
    }
    
    card.className = 'team-card';
    
    const content = document.createElement('div');
    content.className = 'team-card__content';
    
    content.innerHTML = `
        <h3 class="team-card__name">${member.name}</h3>
        <p class="team-card__detail">Roll No: ${member.rollNo}</p>
        <p class="team-card__detail">USN: ${member.usn}</p>
    `;
    
    card.appendChild(content);
    
    // Add 3D hover effect
    card.addEventListener('mousemove', handleCardHover);
    card.addEventListener('mouseleave', resetCardPosition);
    
    return card;
}

function handleCardHover(e) {
    const card = e.currentTarget;
    const rect = card.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;
    
    const rotateX = (y - rect.height / 2) / 20;
    const rotateY = (rect.width / 2 - x) / 20;
    
    card.style.transform = `perspective(1000px) rotateX(${rotateX}deg) rotateY(${rotateY}deg) translateZ(10px)`;
}

function resetCardPosition(e) {
    const card = e.currentTarget;
    card.style.transform = 'perspective(1000px) rotateX(0) rotateY(0) translateZ(0)';
}